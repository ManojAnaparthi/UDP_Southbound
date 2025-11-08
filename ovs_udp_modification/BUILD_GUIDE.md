# Building and Deploying OVS with UDP Support

## Overview

This guide provides step-by-step instructions for compiling Open vSwitch with UDP socket support and deploying it for end-to-end testing with the Ryu UDP controller.

## Prerequisites

### 1. System Requirements

- Ubuntu 20.04/22.04 or Debian-based Linux
- Root/sudo access
- At least 2GB RAM
- 5GB free disk space

### 2. Install Build Dependencies

```bash
# Update package lists
sudo apt-get update

# Install essential build tools
sudo apt-get install -y \
    build-essential \
    autoconf \
    automake \
    libtool \
    pkg-config \
    git

# Install OVS dependencies
sudo apt-get install -y \
    libssl-dev \
    libcap-ng-dev \
    python3-dev \
    python3-pip \
    python3-sphinx \
    libunbound-dev \
    libunwind-dev

# Install optional dependencies
sudo apt-get install -y \
    graphviz \
    groff \
    python3-six
```

### 3. Download Open vSwitch Source

```bash
# Navigate to workspace
cd /home/set-iitgn-vm/Desktop/CN_Project_SDN

# Download OVS source (version 2.17 or latest)
wget https://www.openvswitch.org/releases/openvswitch-2.17.0.tar.gz

# Or clone from git
git clone https://github.com/openvswitch/ovs.git
cd ovs
git checkout v2.17.0  # Use stable version

# Extract tarball if downloaded
# tar xzf openvswitch-2.17.0.tar.gz
# cd openvswitch-2.17.0
```

## Applying UDP Modifications

### Step 1: Copy UDP Implementation Files

```bash
# From CN_Project_SDN directory
cd /home/set-iitgn-vm/Desktop/CN_Project_SDN

# Copy UDP stream implementation
cp ovs_udp_modification/lib/stream-udp.c ovs/lib/

# Copy UDP vconn implementation
cp ovs_udp_modification/lib/vconn-udp.c ovs/lib/
```

### Step 2: Modify Build Configuration

#### Edit `lib/automake.mk`

Add UDP source files to the build:

```bash
cd ovs

# Edit lib/automake.mk
nano lib/automake.mk
```

Find the `lib_libopenvswitch_la_SOURCES` section and add:

```makefile
lib_libopenvswitch_la_SOURCES = \
    lib/stream-udp.c \
    lib/vconn-udp.c \
    # ... existing files ...
```

#### Edit `lib/stream.c`

Register the UDP stream class:

```bash
nano lib/stream.c
```

In the `stream_init()` function, add:

```c
void
stream_init(void)
{
    static struct ovsthread_once once = OVSTHREAD_ONCE_INITIALIZER;

    if (ovsthread_once_start(&once)) {
        stream_register_class(&tcp_stream_class);
        stream_register_class(&unix_stream_class);
        stream_register_class(&udp_stream_class);  // ADD THIS LINE
#ifdef HAVE_OPENSSL
        stream_register_class(&ssl_stream_class);
#endif
        ovsthread_once_done(&once);
    }
}
```

Add external declaration at the top of the file:

```c
extern const struct stream_class udp_stream_class;
```

#### Edit `lib/vconn.c`

Register the UDP vconn class:

```bash
nano lib/vconn.c
```

In the `vconn_init()` function, add:

```c
void
vconn_init(void)
{
    static struct ovsthread_once once = OVSTHREAD_ONCE_INITIALIZER;

    if (ovsthread_once_start(&once)) {
        vconn_register_class(&tcp_vconn_class);
        vconn_register_class(&unix_vconn_class);
        vconn_register_class(&udp_vconn_class);  // ADD THIS LINE
#ifdef HAVE_OPENSSL
        vconn_register_class(&ssl_vconn_class);
#endif
        ovsthread_once_done(&once);
    }
}
```

Add external declaration:

```c
extern const struct vconn_class udp_vconn_class;
```

### Step 3: Apply Optional Connection Manager Patches

For production use, apply the connection manager modifications described in `CONNMGR_MODIFICATIONS.md`. For basic testing, the default connection manager will work.

## Building OVS

### Configure Build

```bash
cd /home/set-iitgn-vm/Desktop/CN_Project_SDN/ovs

# Bootstrap the build system (if from git)
./boot.sh

# Configure with standard options
./configure \
    --prefix=/usr \
    --localstatedir=/var \
    --sysconfdir=/etc \
    --enable-ssl

# Or for development/testing (no install):
./configure --prefix=$PWD/install
```

### Compile

```bash
# Build OVS (use all CPU cores)
make -j$(nproc)

# This takes 5-15 minutes depending on your system
```

### Verify Build

```bash
# Check for compilation errors
echo $?  # Should print 0

# Check for UDP symbols
nm lib/.libs/libopenvswitch.so | grep udp
# Should show: udp_stream_class, udp_vconn_class, etc.

# Run unit tests (optional)
make check
```

## Installation Options

### Option A: System-wide Installation (Replaces existing OVS)

**⚠️ WARNING**: This replaces your system OVS installation. Backup first!

```bash
# Stop existing OVS
sudo systemctl stop openvswitch-switch

# Install
sudo make install

# Initialize database (if fresh install)
sudo mkdir -p /usr/local/etc/openvswitch
sudo ovsdb-tool create /usr/local/etc/openvswitch/conf.db \
    vswitchd/vswitch.ovsschema

# Start services
sudo systemctl start openvswitch-switch
```

### Option B: Run from Build Directory (Recommended for testing)

```bash
# No installation needed - run directly from build dir
cd /home/set-iitgn-vm/Desktop/CN_Project_SDN/ovs

# Create runtime directories
sudo mkdir -p /var/run/openvswitch
sudo mkdir -p /var/log/openvswitch
sudo mkdir -p /etc/openvswitch

# Create database (if not exists)
sudo ovsdb-tool create /etc/openvswitch/conf.db \
    vswitchd/vswitch.ovsschema

# Start ovsdb-server
sudo ./ovsdb/ovsdb-server \
    --remote=punix:/var/run/openvswitch/db.sock \
    --remote=db:Open_vSwitch,Open_vSwitch,manager_options \
    --pidfile --detach

# Start ovs-vswitchd with UDP support
sudo ./vswitchd/ovs-vswitchd \
    --pidfile --detach --log-file=/var/log/openvswitch/ovs-vswitchd.log

# Verify running
ps aux | grep ovs
```

## Testing UDP Support

### 1. Run Unit Tests

```bash
cd /home/set-iitgn-vm/Desktop/CN_Project_SDN

# Test UDP basics
python3 ovs_udp_modification/tests/test_udp_unit.py
```

Expected output:
```
============================================================
 UDP OpenFlow Unit Tests
============================================================

[TEST] UDP socket creation...
[✓] UDP socket created and bound to port 54321

[TEST] OpenFlow message structure...
[✓] OpenFlow HELLO message created: 8 bytes
[✓] Message unpacked correctly: v=4, type=0, len=8, xid=12345

[TEST] UDP send/receive...
[✓] Server received 8 bytes from ('127.0.0.1', 54322)
[✓] Client received 8 bytes

[TEST] Message boundary preservation...
[✓] Message boundaries preserved correctly

============================================================
 Results: 4/4 tests passed
============================================================
```

### 2. Start UDP Controller

```bash
# Terminal 1: Start Ryu UDP controller
cd /home/set-iitgn-vm/Desktop/CN_Project_SDN
python3 -m udp_baseline.controllers.udp_ofp_controller
```

Expected output:
```
[INFO] UDP OpenFlow Controller listening on 0.0.0.0:6633
```

### 3. Configure OVS Bridge with UDP

```bash
# Terminal 2: Configure OVS

# Create test bridge
sudo ovs-vsctl add-br br-test

# Set OpenFlow 1.3
sudo ovs-vsctl set bridge br-test protocols=OpenFlow13

# Set UDP controller
sudo ovs-vsctl set-controller br-test udp:127.0.0.1:6633

# Verify configuration
sudo ovs-vsctl show
```

Expected output:
```
Bridge br-test
    Controller "udp:127.0.0.1:6633"
    Port br-test
        Interface br-test
            type: internal
```

### 4. Verify Connection

Check controller terminal for:
```
[INFO] Received HELLO from ('127.0.0.1', 54321), xid=1
[SEND] HELLO → ('127.0.0.1', 54321)
[SEND] FEATURES_REQUEST → ('127.0.0.1', 54321)
[INFO] Switch connected: DPID=0x0000000000000001
```

Check OVS logs:
```bash
sudo tail -f /var/log/openvswitch/ovs-vswitchd.log | grep -i udp
```

### 5. Run Integration Tests

```bash
# Terminal 3: Run integration test
cd /home/set-iitgn-vm/Desktop/CN_Project_SDN
sudo python3 ovs_udp_modification/tests/test_ovs_udp_integration.py
```

## Troubleshooting

### Build Errors

**Error**: `stream-udp.c: No such file or directory`

**Solution**: Verify files are copied to correct location:
```bash
ls -la ovs/lib/stream-udp.c
ls -la ovs/lib/vconn-udp.c
```

**Error**: `undefined reference to 'udp_stream_class'`

**Solution**: Check that stream class is registered in `lib/stream.c`

### Runtime Errors

**Error**: `ovs-vsctl: unix:/var/run/openvswitch/db.sock: database connection failed`

**Solution**: Start ovsdb-server first:
```bash
sudo ./ovsdb/ovsdb-server \
    --remote=punix:/var/run/openvswitch/db.sock \
    --pidfile --detach
```

**Error**: `Failed to open UDP stream`

**Solution**: Check controller is running and port 6633 is available:
```bash
sudo netstat -ulnp | grep 6633
```

### Connection Issues

**Problem**: Controller shows "No connection"

**Check**:
1. Controller is running: `ps aux | grep udp_ofp_controller`
2. Firewall allows UDP 6633: `sudo ufw status`
3. OVS logs show connection attempt: `sudo ovs-appctl vlog/list`

## Capture and Analyze Traffic

```bash
# Capture UDP OpenFlow traffic
sudo tcpdump -i lo -w /tmp/openflow_udp.pcap port 6633

# Analyze with Wireshark
wireshark /tmp/openflow_udp.pcap
```

## Cleanup

```bash
# Stop OVS
sudo pkill ovs-vswitchd
sudo pkill ovsdb-server

# Delete bridges
sudo ovs-vsctl --if-exists del-br br-test

# Remove runtime files
sudo rm -rf /var/run/openvswitch/*

# Restore original OVS (if needed)
sudo apt-get install --reinstall openvswitch-switch
```

## Next Steps

After successful deployment:

1. **Phase 5**: Run performance benchmarks comparing TCP vs UDP
2. **Phase 6**: Implement reliability mechanisms for critical messages
3. **Phase 7**: Document findings and create final report

## References

- OVS Documentation: https://docs.openvswitch.org/
- OVS Build Guide: https://github.com/openvswitch/ovs/blob/master/Documentation/intro/install/general.rst
- OpenFlow 1.3 Spec: https://www.opennetworking.org/wp-content/uploads/2014/10/openflow-spec-v1.3.0.pdf

---

**Status**: Phase 4 Build Guide Complete  
**Date**: November 8, 2025  
**Next**: Test end-to-end UDP communication
