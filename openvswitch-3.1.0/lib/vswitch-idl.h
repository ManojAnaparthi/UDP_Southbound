/* Generated automatically -- do not modify!    -*- buffer-read-only: t -*- */

#ifndef OVSREC_IDL_HEADER
#define OVSREC_IDL_HEADER 1

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "openvswitch/json.h"
#include "ovsdb-data.h"
#include "ovsdb-idl-provider.h"
#include "smap.h"
#include "uuid.h"

#ifdef  __cplusplus
extern "C" {
#endif


/* AutoAttach table. */
struct ovsrec_autoattach {
	struct ovsdb_idl_row header_;

	/* mappings column. */
	int64_t *key_mappings;
	int64_t *value_mappings;
	size_t n_mappings;

	/* system_description column. */
	char *system_description;	/* Always nonnull. */

	/* system_name column. */
	char *system_name;	/* Always nonnull. */
};

enum ovsrec_autoattach_column_id {
    OVSREC_AUTOATTACH_COL_MAPPINGS,
    OVSREC_AUTOATTACH_COL_SYSTEM_DESCRIPTION,
    OVSREC_AUTOATTACH_COL_SYSTEM_NAME,
    OVSREC_AUTOATTACH_N_COLUMNS
};

#define ovsrec_autoattach_col_mappings (ovsrec_autoattach_columns[OVSREC_AUTOATTACH_COL_MAPPINGS])
#define ovsrec_autoattach_col_system_description (ovsrec_autoattach_columns[OVSREC_AUTOATTACH_COL_SYSTEM_DESCRIPTION])
#define ovsrec_autoattach_col_system_name (ovsrec_autoattach_columns[OVSREC_AUTOATTACH_COL_SYSTEM_NAME])

extern struct ovsdb_idl_column ovsrec_autoattach_columns[OVSREC_AUTOATTACH_N_COLUMNS];
bool ovsrec_server_has_autoattach_table_col_mappings(const struct ovsdb_idl *); 
bool ovsrec_server_has_autoattach_table_col_system_description(const struct ovsdb_idl *); 
bool ovsrec_server_has_autoattach_table_col_system_name(const struct ovsdb_idl *); 

bool ovsrec_server_has_autoattach_table(const struct ovsdb_idl *);
const struct ovsrec_autoattach_table *ovsrec_autoattach_table_get(const struct ovsdb_idl *);
const struct ovsrec_autoattach *ovsrec_autoattach_table_first(const struct ovsrec_autoattach_table *);

#define OVSREC_AUTOATTACH_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_autoattach_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_autoattach_next(ROW))
#define OVSREC_AUTOATTACH_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_autoattach_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_autoattach_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_AUTOATTACH_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_autoattach * ROW__next = ((ROW) = ovsrec_autoattach_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_autoattach_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_AUTOATTACH_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_AUTOATTACH_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_AUTOATTACH_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_autoattach *ovsrec_autoattach_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_autoattach *ovsrec_autoattach_table_get_for_uuid(const struct ovsrec_autoattach_table *, const struct uuid *);
const struct ovsrec_autoattach *ovsrec_autoattach_first(const struct ovsdb_idl *);
const struct ovsrec_autoattach *ovsrec_autoattach_next(const struct ovsrec_autoattach *);
#define OVSREC_AUTOATTACH_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_autoattach_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_autoattach_next(ROW))
#define OVSREC_AUTOATTACH_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_autoattach_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_autoattach_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_AUTOATTACH_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_autoattach * ROW__next = ((ROW) = ovsrec_autoattach_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_autoattach_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_AUTOATTACH_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_AUTOATTACH_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_AUTOATTACH_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_autoattach_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_autoattach_row_get_seqno(const struct ovsrec_autoattach *row, enum ovsdb_idl_change change);
const struct ovsrec_autoattach *ovsrec_autoattach_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_autoattach *ovsrec_autoattach_track_get_next(const struct ovsrec_autoattach *);
#define OVSREC_AUTOATTACH_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_autoattach_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_autoattach_track_get_next(ROW))

const struct ovsrec_autoattach *ovsrec_autoattach_table_track_get_first(const struct ovsrec_autoattach_table *);
#define OVSREC_AUTOATTACH_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_autoattach_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_autoattach_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_autoattach_is_new(const struct ovsrec_autoattach *row)
{
    return ovsrec_autoattach_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_autoattach_is_deleted(const struct ovsrec_autoattach *row)
{
    return ovsrec_autoattach_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_autoattach_index_destroy_row(const struct ovsrec_autoattach *);

struct ovsrec_autoattach *ovsrec_autoattach_index_find(struct ovsdb_idl_index *, const struct ovsrec_autoattach *);

int ovsrec_autoattach_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_autoattach *, 
    const struct ovsrec_autoattach *);
struct ovsdb_idl_cursor ovsrec_autoattach_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_autoattach_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_autoattach *);
struct ovsdb_idl_cursor ovsrec_autoattach_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_autoattach *);

struct ovsrec_autoattach *ovsrec_autoattach_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_AUTOATTACH_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_autoattach_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_autoattach_cursor_data(&cursor__), \
                  !(TO) || ovsrec_autoattach_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_AUTOATTACH_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_autoattach_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_autoattach_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_AUTOATTACH_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_autoattach_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_autoattach_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_autoattach_init(struct ovsrec_autoattach *);
void ovsrec_autoattach_delete(const struct ovsrec_autoattach *);
struct ovsrec_autoattach *ovsrec_autoattach_insert(struct ovsdb_idl_txn *);
struct ovsrec_autoattach *ovsrec_autoattach_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_autoattach_column_id' of
 * the row referenced by 'struct ovsrec_autoattach *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_autoattach_is_updated(const struct ovsrec_autoattach *, enum ovsrec_autoattach_column_id);

void ovsrec_autoattach_verify_mappings(const struct ovsrec_autoattach *);
void ovsrec_autoattach_verify_system_description(const struct ovsrec_autoattach *);
void ovsrec_autoattach_verify_system_name(const struct ovsrec_autoattach *);

const struct ovsdb_datum *ovsrec_autoattach_get_mappings(const struct ovsrec_autoattach *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_autoattach_get_system_description(const struct ovsrec_autoattach *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_autoattach_get_system_name(const struct ovsrec_autoattach *, enum ovsdb_atomic_type key_type);

void ovsrec_autoattach_set_mappings(const struct ovsrec_autoattach *, const int64_t *key_mappings, const int64_t *value_mappings, size_t n_mappings);
void ovsrec_autoattach_set_system_description(const struct ovsrec_autoattach *, const char *system_description);
void ovsrec_autoattach_set_system_name(const struct ovsrec_autoattach *, const char *system_name);

void ovsrec_autoattach_update_mappings_setkey(const struct ovsrec_autoattach *,  int64_t , int64_t );
void ovsrec_autoattach_update_mappings_delkey(const struct ovsrec_autoattach *,  int64_t );
void ovsrec_autoattach_add_clause_mappings(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *key_mappings, const int64_t *value_mappings, size_t n_mappings);
unsigned int ovsrec_autoattach_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_autoattach_add_clause_system_description(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *system_description);
unsigned int ovsrec_autoattach_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_autoattach_add_clause_system_name(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *system_name);
unsigned int ovsrec_autoattach_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_autoattach *ovsrec_autoattach_index_init_row(struct ovsdb_idl_index *);
void ovsrec_autoattach_index_set_mappings(const struct ovsrec_autoattach *,
const int64_t *key_mappings, const int64_t *value_mappings, size_t n_mappings);
void ovsrec_autoattach_index_set_system_description(const struct ovsrec_autoattach *,
const char *system_description);
void ovsrec_autoattach_index_set_system_name(const struct ovsrec_autoattach *,
const char *system_name);

/* Bridge table. */
struct ovsrec_bridge {
	struct ovsdb_idl_row header_;

	/* auto_attach column. */
	struct ovsrec_autoattach *auto_attach;

	/* controller column. */
	struct ovsrec_controller **controller;
	size_t n_controller;

	/* datapath_id column. */
	char *datapath_id;

	/* datapath_type column. */
	char *datapath_type;	/* Always nonnull. */

	/* datapath_version column. */
	char *datapath_version;	/* Always nonnull. */

	/* external_ids column. */
	struct smap external_ids;

	/* fail_mode column. */
	char *fail_mode;

	/* flood_vlans column. */
	int64_t *flood_vlans;
	size_t n_flood_vlans;

	/* flow_tables column. */
	int64_t *key_flow_tables;
	struct ovsrec_flow_table **value_flow_tables;
	size_t n_flow_tables;

	/* ipfix column. */
	struct ovsrec_ipfix *ipfix;

	/* mcast_snooping_enable column. */
	bool mcast_snooping_enable;

	/* mirrors column. */
	struct ovsrec_mirror **mirrors;
	size_t n_mirrors;

	/* name column. */
	char *name;	/* Always nonnull. */

	/* netflow column. */
	struct ovsrec_netflow *netflow;

	/* other_config column. */
	struct smap other_config;

	/* ports column. */
	struct ovsrec_port **ports;
	size_t n_ports;

	/* protocols column. */
	char **protocols;
	size_t n_protocols;

	/* rstp_enable column. */
	bool rstp_enable;

	/* rstp_status column. */
	struct smap rstp_status;

	/* sflow column. */
	struct ovsrec_sflow *sflow;

	/* status column. */
	struct smap status;

	/* stp_enable column. */
	bool stp_enable;
};

enum ovsrec_bridge_column_id {
    OVSREC_BRIDGE_COL_AUTO_ATTACH,
    OVSREC_BRIDGE_COL_CONTROLLER,
    OVSREC_BRIDGE_COL_DATAPATH_ID,
    OVSREC_BRIDGE_COL_DATAPATH_TYPE,
    OVSREC_BRIDGE_COL_DATAPATH_VERSION,
    OVSREC_BRIDGE_COL_EXTERNAL_IDS,
    OVSREC_BRIDGE_COL_FAIL_MODE,
    OVSREC_BRIDGE_COL_FLOOD_VLANS,
    OVSREC_BRIDGE_COL_FLOW_TABLES,
    OVSREC_BRIDGE_COL_IPFIX,
    OVSREC_BRIDGE_COL_MCAST_SNOOPING_ENABLE,
    OVSREC_BRIDGE_COL_MIRRORS,
    OVSREC_BRIDGE_COL_NAME,
    OVSREC_BRIDGE_COL_NETFLOW,
    OVSREC_BRIDGE_COL_OTHER_CONFIG,
    OVSREC_BRIDGE_COL_PORTS,
    OVSREC_BRIDGE_COL_PROTOCOLS,
    OVSREC_BRIDGE_COL_RSTP_ENABLE,
    OVSREC_BRIDGE_COL_RSTP_STATUS,
    OVSREC_BRIDGE_COL_SFLOW,
    OVSREC_BRIDGE_COL_STATUS,
    OVSREC_BRIDGE_COL_STP_ENABLE,
    OVSREC_BRIDGE_N_COLUMNS
};

#define ovsrec_bridge_col_auto_attach (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_AUTO_ATTACH])
#define ovsrec_bridge_col_controller (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_CONTROLLER])
#define ovsrec_bridge_col_datapath_id (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_DATAPATH_ID])
#define ovsrec_bridge_col_datapath_type (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_DATAPATH_TYPE])
#define ovsrec_bridge_col_datapath_version (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_DATAPATH_VERSION])
#define ovsrec_bridge_col_external_ids (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_EXTERNAL_IDS])
#define ovsrec_bridge_col_fail_mode (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_FAIL_MODE])
#define ovsrec_bridge_col_flood_vlans (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_FLOOD_VLANS])
#define ovsrec_bridge_col_flow_tables (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_FLOW_TABLES])
#define ovsrec_bridge_col_ipfix (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_IPFIX])
#define ovsrec_bridge_col_mcast_snooping_enable (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_MCAST_SNOOPING_ENABLE])
#define ovsrec_bridge_col_mirrors (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_MIRRORS])
#define ovsrec_bridge_col_name (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_NAME])
#define ovsrec_bridge_col_netflow (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_NETFLOW])
#define ovsrec_bridge_col_other_config (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_OTHER_CONFIG])
#define ovsrec_bridge_col_ports (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_PORTS])
#define ovsrec_bridge_col_protocols (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_PROTOCOLS])
#define ovsrec_bridge_col_rstp_enable (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_RSTP_ENABLE])
#define ovsrec_bridge_col_rstp_status (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_RSTP_STATUS])
#define ovsrec_bridge_col_sflow (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_SFLOW])
#define ovsrec_bridge_col_status (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_STATUS])
#define ovsrec_bridge_col_stp_enable (ovsrec_bridge_columns[OVSREC_BRIDGE_COL_STP_ENABLE])

extern struct ovsdb_idl_column ovsrec_bridge_columns[OVSREC_BRIDGE_N_COLUMNS];
bool ovsrec_server_has_bridge_table_col_auto_attach(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_controller(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_datapath_id(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_datapath_type(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_datapath_version(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_external_ids(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_fail_mode(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_flood_vlans(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_flow_tables(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_ipfix(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_mcast_snooping_enable(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_mirrors(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_name(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_netflow(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_other_config(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_ports(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_protocols(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_rstp_enable(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_rstp_status(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_sflow(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_status(const struct ovsdb_idl *); 
bool ovsrec_server_has_bridge_table_col_stp_enable(const struct ovsdb_idl *); 

bool ovsrec_server_has_bridge_table(const struct ovsdb_idl *);
const struct ovsrec_bridge_table *ovsrec_bridge_table_get(const struct ovsdb_idl *);
const struct ovsrec_bridge *ovsrec_bridge_table_first(const struct ovsrec_bridge_table *);

#define OVSREC_BRIDGE_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_bridge_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_bridge_next(ROW))
#define OVSREC_BRIDGE_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_bridge_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_bridge_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_BRIDGE_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_bridge * ROW__next = ((ROW) = ovsrec_bridge_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_bridge_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_BRIDGE_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_BRIDGE_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_BRIDGE_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_bridge *ovsrec_bridge_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_bridge *ovsrec_bridge_table_get_for_uuid(const struct ovsrec_bridge_table *, const struct uuid *);
const struct ovsrec_bridge *ovsrec_bridge_first(const struct ovsdb_idl *);
const struct ovsrec_bridge *ovsrec_bridge_next(const struct ovsrec_bridge *);
#define OVSREC_BRIDGE_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_bridge_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_bridge_next(ROW))
#define OVSREC_BRIDGE_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_bridge_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_bridge_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_BRIDGE_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_bridge * ROW__next = ((ROW) = ovsrec_bridge_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_bridge_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_BRIDGE_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_BRIDGE_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_BRIDGE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_bridge_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_bridge_row_get_seqno(const struct ovsrec_bridge *row, enum ovsdb_idl_change change);
const struct ovsrec_bridge *ovsrec_bridge_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_bridge *ovsrec_bridge_track_get_next(const struct ovsrec_bridge *);
#define OVSREC_BRIDGE_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_bridge_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_bridge_track_get_next(ROW))

const struct ovsrec_bridge *ovsrec_bridge_table_track_get_first(const struct ovsrec_bridge_table *);
#define OVSREC_BRIDGE_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_bridge_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_bridge_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_bridge_is_new(const struct ovsrec_bridge *row)
{
    return ovsrec_bridge_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_bridge_is_deleted(const struct ovsrec_bridge *row)
{
    return ovsrec_bridge_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_bridge_index_destroy_row(const struct ovsrec_bridge *);

struct ovsrec_bridge *ovsrec_bridge_index_find(struct ovsdb_idl_index *, const struct ovsrec_bridge *);

int ovsrec_bridge_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_bridge *, 
    const struct ovsrec_bridge *);
struct ovsdb_idl_cursor ovsrec_bridge_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_bridge_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_bridge *);
struct ovsdb_idl_cursor ovsrec_bridge_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_bridge *);

struct ovsrec_bridge *ovsrec_bridge_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_BRIDGE_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_bridge_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_bridge_cursor_data(&cursor__), \
                  !(TO) || ovsrec_bridge_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_BRIDGE_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_bridge_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_bridge_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_BRIDGE_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_bridge_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_bridge_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_bridge_init(struct ovsrec_bridge *);
void ovsrec_bridge_delete(const struct ovsrec_bridge *);
struct ovsrec_bridge *ovsrec_bridge_insert(struct ovsdb_idl_txn *);
struct ovsrec_bridge *ovsrec_bridge_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_bridge_column_id' of
 * the row referenced by 'struct ovsrec_bridge *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_bridge_is_updated(const struct ovsrec_bridge *, enum ovsrec_bridge_column_id);

void ovsrec_bridge_verify_auto_attach(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_controller(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_datapath_id(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_datapath_type(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_datapath_version(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_external_ids(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_fail_mode(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_flood_vlans(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_flow_tables(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_ipfix(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_mcast_snooping_enable(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_mirrors(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_name(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_netflow(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_other_config(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_ports(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_protocols(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_rstp_enable(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_rstp_status(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_sflow(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_status(const struct ovsrec_bridge *);
void ovsrec_bridge_verify_stp_enable(const struct ovsrec_bridge *);

const struct ovsdb_datum *ovsrec_bridge_get_auto_attach(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_bridge_get_controller(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_bridge_get_datapath_id(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_bridge_get_datapath_type(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_bridge_get_datapath_version(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_bridge_get_external_ids(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_bridge_get_fail_mode(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_bridge_get_flood_vlans(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_bridge_get_flow_tables(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_bridge_get_ipfix(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_bridge_get_mcast_snooping_enable(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_bridge_get_mirrors(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_bridge_get_name(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_bridge_get_netflow(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_bridge_get_other_config(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_bridge_get_ports(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_bridge_get_protocols(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_bridge_get_rstp_enable(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_bridge_get_rstp_status(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_bridge_get_sflow(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_bridge_get_status(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_bridge_get_stp_enable(const struct ovsrec_bridge *, enum ovsdb_atomic_type key_type);

void ovsrec_bridge_set_auto_attach(const struct ovsrec_bridge *, const struct ovsrec_autoattach *auto_attach);
void ovsrec_bridge_set_controller(const struct ovsrec_bridge *, struct ovsrec_controller **controller, size_t n_controller);
void ovsrec_bridge_set_datapath_id(const struct ovsrec_bridge *, const char *datapath_id);
void ovsrec_bridge_set_datapath_type(const struct ovsrec_bridge *, const char *datapath_type);
void ovsrec_bridge_set_datapath_version(const struct ovsrec_bridge *, const char *datapath_version);
void ovsrec_bridge_set_external_ids(const struct ovsrec_bridge *, const struct smap *);
void ovsrec_bridge_set_fail_mode(const struct ovsrec_bridge *, const char *fail_mode);
void ovsrec_bridge_set_flood_vlans(const struct ovsrec_bridge *, const int64_t *flood_vlans, size_t n_flood_vlans);
void ovsrec_bridge_set_flow_tables(const struct ovsrec_bridge *, const int64_t *key_flow_tables, struct ovsrec_flow_table **value_flow_tables, size_t n_flow_tables);
void ovsrec_bridge_set_ipfix(const struct ovsrec_bridge *, const struct ovsrec_ipfix *ipfix);
void ovsrec_bridge_set_mcast_snooping_enable(const struct ovsrec_bridge *, bool mcast_snooping_enable);
void ovsrec_bridge_set_mirrors(const struct ovsrec_bridge *, struct ovsrec_mirror **mirrors, size_t n_mirrors);
void ovsrec_bridge_set_name(const struct ovsrec_bridge *, const char *name);
void ovsrec_bridge_set_netflow(const struct ovsrec_bridge *, const struct ovsrec_netflow *netflow);
void ovsrec_bridge_set_other_config(const struct ovsrec_bridge *, const struct smap *);
void ovsrec_bridge_set_ports(const struct ovsrec_bridge *, struct ovsrec_port **ports, size_t n_ports);
void ovsrec_bridge_set_protocols(const struct ovsrec_bridge *, const char **protocols, size_t n_protocols);
void ovsrec_bridge_set_rstp_enable(const struct ovsrec_bridge *, bool rstp_enable);
void ovsrec_bridge_set_rstp_status(const struct ovsrec_bridge *, const struct smap *);
void ovsrec_bridge_set_sflow(const struct ovsrec_bridge *, const struct ovsrec_sflow *sflow);
void ovsrec_bridge_set_status(const struct ovsrec_bridge *, const struct smap *);
void ovsrec_bridge_set_stp_enable(const struct ovsrec_bridge *, bool stp_enable);

void ovsrec_bridge_update_auto_attach_addvalue(const struct ovsrec_bridge *,  const struct ovsrec_autoattach *);
void ovsrec_bridge_update_auto_attach_delvalue(const struct ovsrec_bridge *,  const struct ovsrec_autoattach *);
void ovsrec_bridge_add_clause_auto_attach(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct uuid *auto_attach);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_update_controller_addvalue(const struct ovsrec_bridge *,  const struct ovsrec_controller *);
void ovsrec_bridge_update_controller_delvalue(const struct ovsrec_bridge *,  const struct ovsrec_controller *);
void ovsrec_bridge_add_clause_controller(struct ovsdb_idl_condition *, enum ovsdb_function function, struct uuid **controller, size_t n_controller);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_update_datapath_id_addvalue(const struct ovsrec_bridge *,  const char *);
void ovsrec_bridge_update_datapath_id_delvalue(const struct ovsrec_bridge *,  const char *);
void ovsrec_bridge_add_clause_datapath_id(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *datapath_id);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_add_clause_datapath_type(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *datapath_type);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_add_clause_datapath_version(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *datapath_version);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_update_external_ids_setkey(const struct ovsrec_bridge *,  const char *, const char *);
void ovsrec_bridge_update_external_ids_delkey(const struct ovsrec_bridge *,  const char *);
void ovsrec_bridge_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_update_fail_mode_addvalue(const struct ovsrec_bridge *,  const char *);
void ovsrec_bridge_update_fail_mode_delvalue(const struct ovsrec_bridge *,  const char *);
void ovsrec_bridge_add_clause_fail_mode(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *fail_mode);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_update_flood_vlans_addvalue(const struct ovsrec_bridge *,  int64_t );
void ovsrec_bridge_update_flood_vlans_delvalue(const struct ovsrec_bridge *,  int64_t );
void ovsrec_bridge_add_clause_flood_vlans(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *flood_vlans, size_t n_flood_vlans);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_update_flow_tables_setkey(const struct ovsrec_bridge *,  int64_t , const struct ovsrec_flow_table *);
void ovsrec_bridge_update_flow_tables_delkey(const struct ovsrec_bridge *,  int64_t );
void ovsrec_bridge_add_clause_flow_tables(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *key_flow_tables, struct uuid **value_flow_tables, size_t n_flow_tables);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_update_ipfix_addvalue(const struct ovsrec_bridge *,  const struct ovsrec_ipfix *);
void ovsrec_bridge_update_ipfix_delvalue(const struct ovsrec_bridge *,  const struct ovsrec_ipfix *);
void ovsrec_bridge_add_clause_ipfix(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct uuid *ipfix);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_add_clause_mcast_snooping_enable(struct ovsdb_idl_condition *, enum ovsdb_function function, bool mcast_snooping_enable);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_update_mirrors_addvalue(const struct ovsrec_bridge *,  const struct ovsrec_mirror *);
void ovsrec_bridge_update_mirrors_delvalue(const struct ovsrec_bridge *,  const struct ovsrec_mirror *);
void ovsrec_bridge_add_clause_mirrors(struct ovsdb_idl_condition *, enum ovsdb_function function, struct uuid **mirrors, size_t n_mirrors);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_add_clause_name(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *name);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_update_netflow_addvalue(const struct ovsrec_bridge *,  const struct ovsrec_netflow *);
void ovsrec_bridge_update_netflow_delvalue(const struct ovsrec_bridge *,  const struct ovsrec_netflow *);
void ovsrec_bridge_add_clause_netflow(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct uuid *netflow);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_update_other_config_setkey(const struct ovsrec_bridge *,  const char *, const char *);
void ovsrec_bridge_update_other_config_delkey(const struct ovsrec_bridge *,  const char *);
void ovsrec_bridge_add_clause_other_config(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_update_ports_addvalue(const struct ovsrec_bridge *,  const struct ovsrec_port *);
void ovsrec_bridge_update_ports_delvalue(const struct ovsrec_bridge *,  const struct ovsrec_port *);
void ovsrec_bridge_add_clause_ports(struct ovsdb_idl_condition *, enum ovsdb_function function, struct uuid **ports, size_t n_ports);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_update_protocols_addvalue(const struct ovsrec_bridge *,  const char *);
void ovsrec_bridge_update_protocols_delvalue(const struct ovsrec_bridge *,  const char *);
void ovsrec_bridge_add_clause_protocols(struct ovsdb_idl_condition *, enum ovsdb_function function, const char **protocols, size_t n_protocols);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_add_clause_rstp_enable(struct ovsdb_idl_condition *, enum ovsdb_function function, bool rstp_enable);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_update_rstp_status_setkey(const struct ovsrec_bridge *,  const char *, const char *);
void ovsrec_bridge_update_rstp_status_delkey(const struct ovsrec_bridge *,  const char *);
void ovsrec_bridge_add_clause_rstp_status(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_update_sflow_addvalue(const struct ovsrec_bridge *,  const struct ovsrec_sflow *);
void ovsrec_bridge_update_sflow_delvalue(const struct ovsrec_bridge *,  const struct ovsrec_sflow *);
void ovsrec_bridge_add_clause_sflow(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct uuid *sflow);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_update_status_setkey(const struct ovsrec_bridge *,  const char *, const char *);
void ovsrec_bridge_update_status_delkey(const struct ovsrec_bridge *,  const char *);
void ovsrec_bridge_add_clause_status(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_bridge_add_clause_stp_enable(struct ovsdb_idl_condition *, enum ovsdb_function function, bool stp_enable);
unsigned int ovsrec_bridge_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_bridge *ovsrec_bridge_index_init_row(struct ovsdb_idl_index *);
void ovsrec_bridge_index_set_auto_attach(const struct ovsrec_bridge *,
const struct ovsrec_autoattach *auto_attach);
void ovsrec_bridge_index_set_controller(const struct ovsrec_bridge *,
struct ovsrec_controller **controller, size_t n_controller);
void ovsrec_bridge_index_set_datapath_id(const struct ovsrec_bridge *,
const char *datapath_id);
void ovsrec_bridge_index_set_datapath_type(const struct ovsrec_bridge *,
const char *datapath_type);
void ovsrec_bridge_index_set_datapath_version(const struct ovsrec_bridge *,
const char *datapath_version);
void ovsrec_bridge_index_set_external_ids(const struct ovsrec_bridge *,
const struct smap *);
void ovsrec_bridge_index_set_fail_mode(const struct ovsrec_bridge *,
const char *fail_mode);
void ovsrec_bridge_index_set_flood_vlans(const struct ovsrec_bridge *,
const int64_t *flood_vlans, size_t n_flood_vlans);
void ovsrec_bridge_index_set_flow_tables(const struct ovsrec_bridge *,
const int64_t *key_flow_tables, struct ovsrec_flow_table **value_flow_tables, size_t n_flow_tables);
void ovsrec_bridge_index_set_ipfix(const struct ovsrec_bridge *,
const struct ovsrec_ipfix *ipfix);
void ovsrec_bridge_index_set_mcast_snooping_enable(const struct ovsrec_bridge *,
bool mcast_snooping_enable);
void ovsrec_bridge_index_set_mirrors(const struct ovsrec_bridge *,
struct ovsrec_mirror **mirrors, size_t n_mirrors);
void ovsrec_bridge_index_set_name(const struct ovsrec_bridge *,
const char *name);
void ovsrec_bridge_index_set_netflow(const struct ovsrec_bridge *,
const struct ovsrec_netflow *netflow);
void ovsrec_bridge_index_set_other_config(const struct ovsrec_bridge *,
const struct smap *);
void ovsrec_bridge_index_set_ports(const struct ovsrec_bridge *,
struct ovsrec_port **ports, size_t n_ports);
void ovsrec_bridge_index_set_protocols(const struct ovsrec_bridge *,
const char **protocols, size_t n_protocols);
void ovsrec_bridge_index_set_rstp_enable(const struct ovsrec_bridge *,
bool rstp_enable);
void ovsrec_bridge_index_set_rstp_status(const struct ovsrec_bridge *,
const struct smap *);
void ovsrec_bridge_index_set_sflow(const struct ovsrec_bridge *,
const struct ovsrec_sflow *sflow);
void ovsrec_bridge_index_set_status(const struct ovsrec_bridge *,
const struct smap *);
void ovsrec_bridge_index_set_stp_enable(const struct ovsrec_bridge *,
bool stp_enable);

/* CT_Timeout_Policy table. */
struct ovsrec_ct_timeout_policy {
	struct ovsdb_idl_row header_;

	/* external_ids column. */
	struct smap external_ids;

	/* timeouts column. */
	char **key_timeouts;
	int64_t *value_timeouts;
	size_t n_timeouts;
};

enum ovsrec_ct_timeout_policy_column_id {
    OVSREC_CT_TIMEOUT_POLICY_COL_EXTERNAL_IDS,
    OVSREC_CT_TIMEOUT_POLICY_COL_TIMEOUTS,
    OVSREC_CT_TIMEOUT_POLICY_N_COLUMNS
};

#define ovsrec_ct_timeout_policy_col_external_ids (ovsrec_ct_timeout_policy_columns[OVSREC_CT_TIMEOUT_POLICY_COL_EXTERNAL_IDS])
#define ovsrec_ct_timeout_policy_col_timeouts (ovsrec_ct_timeout_policy_columns[OVSREC_CT_TIMEOUT_POLICY_COL_TIMEOUTS])

extern struct ovsdb_idl_column ovsrec_ct_timeout_policy_columns[OVSREC_CT_TIMEOUT_POLICY_N_COLUMNS];
bool ovsrec_server_has_ct_timeout_policy_table_col_external_ids(const struct ovsdb_idl *); 
bool ovsrec_server_has_ct_timeout_policy_table_col_timeouts(const struct ovsdb_idl *); 

bool ovsrec_server_has_ct_timeout_policy_table(const struct ovsdb_idl *);
const struct ovsrec_ct_timeout_policy_table *ovsrec_ct_timeout_policy_table_get(const struct ovsdb_idl *);
const struct ovsrec_ct_timeout_policy *ovsrec_ct_timeout_policy_table_first(const struct ovsrec_ct_timeout_policy_table *);

#define OVSREC_CT_TIMEOUT_POLICY_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_ct_timeout_policy_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_ct_timeout_policy_next(ROW))
#define OVSREC_CT_TIMEOUT_POLICY_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_ct_timeout_policy_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_ct_timeout_policy_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_CT_TIMEOUT_POLICY_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_ct_timeout_policy * ROW__next = ((ROW) = ovsrec_ct_timeout_policy_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_ct_timeout_policy_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_CT_TIMEOUT_POLICY_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_CT_TIMEOUT_POLICY_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_CT_TIMEOUT_POLICY_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_ct_timeout_policy *ovsrec_ct_timeout_policy_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_ct_timeout_policy *ovsrec_ct_timeout_policy_table_get_for_uuid(const struct ovsrec_ct_timeout_policy_table *, const struct uuid *);
const struct ovsrec_ct_timeout_policy *ovsrec_ct_timeout_policy_first(const struct ovsdb_idl *);
const struct ovsrec_ct_timeout_policy *ovsrec_ct_timeout_policy_next(const struct ovsrec_ct_timeout_policy *);
#define OVSREC_CT_TIMEOUT_POLICY_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_ct_timeout_policy_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_ct_timeout_policy_next(ROW))
#define OVSREC_CT_TIMEOUT_POLICY_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_ct_timeout_policy_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_ct_timeout_policy_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_CT_TIMEOUT_POLICY_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_ct_timeout_policy * ROW__next = ((ROW) = ovsrec_ct_timeout_policy_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_ct_timeout_policy_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_CT_TIMEOUT_POLICY_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_CT_TIMEOUT_POLICY_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_CT_TIMEOUT_POLICY_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_ct_timeout_policy_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_ct_timeout_policy_row_get_seqno(const struct ovsrec_ct_timeout_policy *row, enum ovsdb_idl_change change);
const struct ovsrec_ct_timeout_policy *ovsrec_ct_timeout_policy_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_ct_timeout_policy *ovsrec_ct_timeout_policy_track_get_next(const struct ovsrec_ct_timeout_policy *);
#define OVSREC_CT_TIMEOUT_POLICY_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_ct_timeout_policy_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_ct_timeout_policy_track_get_next(ROW))

const struct ovsrec_ct_timeout_policy *ovsrec_ct_timeout_policy_table_track_get_first(const struct ovsrec_ct_timeout_policy_table *);
#define OVSREC_CT_TIMEOUT_POLICY_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_ct_timeout_policy_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_ct_timeout_policy_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_ct_timeout_policy_is_new(const struct ovsrec_ct_timeout_policy *row)
{
    return ovsrec_ct_timeout_policy_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_ct_timeout_policy_is_deleted(const struct ovsrec_ct_timeout_policy *row)
{
    return ovsrec_ct_timeout_policy_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_ct_timeout_policy_index_destroy_row(const struct ovsrec_ct_timeout_policy *);

struct ovsrec_ct_timeout_policy *ovsrec_ct_timeout_policy_index_find(struct ovsdb_idl_index *, const struct ovsrec_ct_timeout_policy *);

int ovsrec_ct_timeout_policy_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_ct_timeout_policy *, 
    const struct ovsrec_ct_timeout_policy *);
struct ovsdb_idl_cursor ovsrec_ct_timeout_policy_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_ct_timeout_policy_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_ct_timeout_policy *);
struct ovsdb_idl_cursor ovsrec_ct_timeout_policy_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_ct_timeout_policy *);

struct ovsrec_ct_timeout_policy *ovsrec_ct_timeout_policy_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_CT_TIMEOUT_POLICY_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_ct_timeout_policy_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_ct_timeout_policy_cursor_data(&cursor__), \
                  !(TO) || ovsrec_ct_timeout_policy_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_CT_TIMEOUT_POLICY_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_ct_timeout_policy_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_ct_timeout_policy_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_CT_TIMEOUT_POLICY_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_ct_timeout_policy_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_ct_timeout_policy_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_ct_timeout_policy_init(struct ovsrec_ct_timeout_policy *);
void ovsrec_ct_timeout_policy_delete(const struct ovsrec_ct_timeout_policy *);
struct ovsrec_ct_timeout_policy *ovsrec_ct_timeout_policy_insert(struct ovsdb_idl_txn *);
struct ovsrec_ct_timeout_policy *ovsrec_ct_timeout_policy_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_ct_timeout_policy_column_id' of
 * the row referenced by 'struct ovsrec_ct_timeout_policy *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_ct_timeout_policy_is_updated(const struct ovsrec_ct_timeout_policy *, enum ovsrec_ct_timeout_policy_column_id);

void ovsrec_ct_timeout_policy_verify_external_ids(const struct ovsrec_ct_timeout_policy *);
void ovsrec_ct_timeout_policy_verify_timeouts(const struct ovsrec_ct_timeout_policy *);

const struct ovsdb_datum *ovsrec_ct_timeout_policy_get_external_ids(const struct ovsrec_ct_timeout_policy *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_ct_timeout_policy_get_timeouts(const struct ovsrec_ct_timeout_policy *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);

void ovsrec_ct_timeout_policy_set_external_ids(const struct ovsrec_ct_timeout_policy *, const struct smap *);
void ovsrec_ct_timeout_policy_set_timeouts(const struct ovsrec_ct_timeout_policy *, const char **key_timeouts, const int64_t *value_timeouts, size_t n_timeouts);

void ovsrec_ct_timeout_policy_update_external_ids_setkey(const struct ovsrec_ct_timeout_policy *,  const char *, const char *);
void ovsrec_ct_timeout_policy_update_external_ids_delkey(const struct ovsrec_ct_timeout_policy *,  const char *);
void ovsrec_ct_timeout_policy_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_ct_timeout_policy_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_ct_timeout_policy_update_timeouts_setkey(const struct ovsrec_ct_timeout_policy *,  const char *, int64_t );
void ovsrec_ct_timeout_policy_update_timeouts_delkey(const struct ovsrec_ct_timeout_policy *,  const char *);
void ovsrec_ct_timeout_policy_add_clause_timeouts(struct ovsdb_idl_condition *, enum ovsdb_function function, const char **key_timeouts, const int64_t *value_timeouts, size_t n_timeouts);
unsigned int ovsrec_ct_timeout_policy_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_ct_timeout_policy *ovsrec_ct_timeout_policy_index_init_row(struct ovsdb_idl_index *);
void ovsrec_ct_timeout_policy_index_set_external_ids(const struct ovsrec_ct_timeout_policy *,
const struct smap *);
void ovsrec_ct_timeout_policy_index_set_timeouts(const struct ovsrec_ct_timeout_policy *,
const char **key_timeouts, const int64_t *value_timeouts, size_t n_timeouts);

/* CT_Zone table. */
struct ovsrec_ct_zone {
	struct ovsdb_idl_row header_;

	/* external_ids column. */
	struct smap external_ids;

	/* timeout_policy column. */
	struct ovsrec_ct_timeout_policy *timeout_policy;
};

enum ovsrec_ct_zone_column_id {
    OVSREC_CT_ZONE_COL_EXTERNAL_IDS,
    OVSREC_CT_ZONE_COL_TIMEOUT_POLICY,
    OVSREC_CT_ZONE_N_COLUMNS
};

#define ovsrec_ct_zone_col_external_ids (ovsrec_ct_zone_columns[OVSREC_CT_ZONE_COL_EXTERNAL_IDS])
#define ovsrec_ct_zone_col_timeout_policy (ovsrec_ct_zone_columns[OVSREC_CT_ZONE_COL_TIMEOUT_POLICY])

extern struct ovsdb_idl_column ovsrec_ct_zone_columns[OVSREC_CT_ZONE_N_COLUMNS];
bool ovsrec_server_has_ct_zone_table_col_external_ids(const struct ovsdb_idl *); 
bool ovsrec_server_has_ct_zone_table_col_timeout_policy(const struct ovsdb_idl *); 

bool ovsrec_server_has_ct_zone_table(const struct ovsdb_idl *);
const struct ovsrec_ct_zone_table *ovsrec_ct_zone_table_get(const struct ovsdb_idl *);
const struct ovsrec_ct_zone *ovsrec_ct_zone_table_first(const struct ovsrec_ct_zone_table *);

#define OVSREC_CT_ZONE_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_ct_zone_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_ct_zone_next(ROW))
#define OVSREC_CT_ZONE_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_ct_zone_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_ct_zone_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_CT_ZONE_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_ct_zone * ROW__next = ((ROW) = ovsrec_ct_zone_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_ct_zone_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_CT_ZONE_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_CT_ZONE_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_CT_ZONE_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_ct_zone *ovsrec_ct_zone_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_ct_zone *ovsrec_ct_zone_table_get_for_uuid(const struct ovsrec_ct_zone_table *, const struct uuid *);
const struct ovsrec_ct_zone *ovsrec_ct_zone_first(const struct ovsdb_idl *);
const struct ovsrec_ct_zone *ovsrec_ct_zone_next(const struct ovsrec_ct_zone *);
#define OVSREC_CT_ZONE_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_ct_zone_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_ct_zone_next(ROW))
#define OVSREC_CT_ZONE_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_ct_zone_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_ct_zone_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_CT_ZONE_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_ct_zone * ROW__next = ((ROW) = ovsrec_ct_zone_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_ct_zone_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_CT_ZONE_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_CT_ZONE_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_CT_ZONE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_ct_zone_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_ct_zone_row_get_seqno(const struct ovsrec_ct_zone *row, enum ovsdb_idl_change change);
const struct ovsrec_ct_zone *ovsrec_ct_zone_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_ct_zone *ovsrec_ct_zone_track_get_next(const struct ovsrec_ct_zone *);
#define OVSREC_CT_ZONE_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_ct_zone_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_ct_zone_track_get_next(ROW))

const struct ovsrec_ct_zone *ovsrec_ct_zone_table_track_get_first(const struct ovsrec_ct_zone_table *);
#define OVSREC_CT_ZONE_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_ct_zone_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_ct_zone_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_ct_zone_is_new(const struct ovsrec_ct_zone *row)
{
    return ovsrec_ct_zone_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_ct_zone_is_deleted(const struct ovsrec_ct_zone *row)
{
    return ovsrec_ct_zone_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_ct_zone_index_destroy_row(const struct ovsrec_ct_zone *);

struct ovsrec_ct_zone *ovsrec_ct_zone_index_find(struct ovsdb_idl_index *, const struct ovsrec_ct_zone *);

int ovsrec_ct_zone_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_ct_zone *, 
    const struct ovsrec_ct_zone *);
struct ovsdb_idl_cursor ovsrec_ct_zone_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_ct_zone_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_ct_zone *);
struct ovsdb_idl_cursor ovsrec_ct_zone_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_ct_zone *);

struct ovsrec_ct_zone *ovsrec_ct_zone_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_CT_ZONE_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_ct_zone_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_ct_zone_cursor_data(&cursor__), \
                  !(TO) || ovsrec_ct_zone_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_CT_ZONE_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_ct_zone_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_ct_zone_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_CT_ZONE_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_ct_zone_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_ct_zone_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_ct_zone_init(struct ovsrec_ct_zone *);
void ovsrec_ct_zone_delete(const struct ovsrec_ct_zone *);
struct ovsrec_ct_zone *ovsrec_ct_zone_insert(struct ovsdb_idl_txn *);
struct ovsrec_ct_zone *ovsrec_ct_zone_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_ct_zone_column_id' of
 * the row referenced by 'struct ovsrec_ct_zone *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_ct_zone_is_updated(const struct ovsrec_ct_zone *, enum ovsrec_ct_zone_column_id);

void ovsrec_ct_zone_verify_external_ids(const struct ovsrec_ct_zone *);
void ovsrec_ct_zone_verify_timeout_policy(const struct ovsrec_ct_zone *);

const struct ovsdb_datum *ovsrec_ct_zone_get_external_ids(const struct ovsrec_ct_zone *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_ct_zone_get_timeout_policy(const struct ovsrec_ct_zone *, enum ovsdb_atomic_type key_type);

void ovsrec_ct_zone_set_external_ids(const struct ovsrec_ct_zone *, const struct smap *);
void ovsrec_ct_zone_set_timeout_policy(const struct ovsrec_ct_zone *, const struct ovsrec_ct_timeout_policy *timeout_policy);

void ovsrec_ct_zone_update_external_ids_setkey(const struct ovsrec_ct_zone *,  const char *, const char *);
void ovsrec_ct_zone_update_external_ids_delkey(const struct ovsrec_ct_zone *,  const char *);
void ovsrec_ct_zone_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_ct_zone_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_ct_zone_update_timeout_policy_addvalue(const struct ovsrec_ct_zone *,  const struct ovsrec_ct_timeout_policy *);
void ovsrec_ct_zone_update_timeout_policy_delvalue(const struct ovsrec_ct_zone *,  const struct ovsrec_ct_timeout_policy *);
void ovsrec_ct_zone_add_clause_timeout_policy(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct uuid *timeout_policy);
unsigned int ovsrec_ct_zone_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_ct_zone *ovsrec_ct_zone_index_init_row(struct ovsdb_idl_index *);
void ovsrec_ct_zone_index_set_external_ids(const struct ovsrec_ct_zone *,
const struct smap *);
void ovsrec_ct_zone_index_set_timeout_policy(const struct ovsrec_ct_zone *,
const struct ovsrec_ct_timeout_policy *timeout_policy);

/* Controller table. */
struct ovsrec_controller {
	struct ovsdb_idl_row header_;

	/* connection_mode column. */
	char *connection_mode;

	/* controller_burst_limit column. */
	int64_t *controller_burst_limit;
	size_t n_controller_burst_limit;

	/* controller_queue_size column. */
	int64_t *controller_queue_size;
	size_t n_controller_queue_size;

	/* controller_rate_limit column. */
	int64_t *controller_rate_limit;
	size_t n_controller_rate_limit;

	/* enable_async_messages column. */
	bool *enable_async_messages;
	size_t n_enable_async_messages;

	/* external_ids column. */
	struct smap external_ids;

	/* inactivity_probe column. */
	int64_t *inactivity_probe;
	size_t n_inactivity_probe;

	/* is_connected column. */
	bool is_connected;

	/* local_gateway column. */
	char *local_gateway;

	/* local_ip column. */
	char *local_ip;

	/* local_netmask column. */
	char *local_netmask;

	/* max_backoff column. */
	int64_t *max_backoff;
	size_t n_max_backoff;

	/* other_config column. */
	struct smap other_config;

	/* role column. */
	char *role;

	/* status column. */
	struct smap status;

	/* target column. */
	char *target;	/* Always nonnull. */

	/* type column. */
	char *type;
};

enum ovsrec_controller_column_id {
    OVSREC_CONTROLLER_COL_CONNECTION_MODE,
    OVSREC_CONTROLLER_COL_CONTROLLER_BURST_LIMIT,
    OVSREC_CONTROLLER_COL_CONTROLLER_QUEUE_SIZE,
    OVSREC_CONTROLLER_COL_CONTROLLER_RATE_LIMIT,
    OVSREC_CONTROLLER_COL_ENABLE_ASYNC_MESSAGES,
    OVSREC_CONTROLLER_COL_EXTERNAL_IDS,
    OVSREC_CONTROLLER_COL_INACTIVITY_PROBE,
    OVSREC_CONTROLLER_COL_IS_CONNECTED,
    OVSREC_CONTROLLER_COL_LOCAL_GATEWAY,
    OVSREC_CONTROLLER_COL_LOCAL_IP,
    OVSREC_CONTROLLER_COL_LOCAL_NETMASK,
    OVSREC_CONTROLLER_COL_MAX_BACKOFF,
    OVSREC_CONTROLLER_COL_OTHER_CONFIG,
    OVSREC_CONTROLLER_COL_ROLE,
    OVSREC_CONTROLLER_COL_STATUS,
    OVSREC_CONTROLLER_COL_TARGET,
    OVSREC_CONTROLLER_COL_TYPE,
    OVSREC_CONTROLLER_N_COLUMNS
};

#define ovsrec_controller_col_connection_mode (ovsrec_controller_columns[OVSREC_CONTROLLER_COL_CONNECTION_MODE])
#define ovsrec_controller_col_controller_burst_limit (ovsrec_controller_columns[OVSREC_CONTROLLER_COL_CONTROLLER_BURST_LIMIT])
#define ovsrec_controller_col_controller_queue_size (ovsrec_controller_columns[OVSREC_CONTROLLER_COL_CONTROLLER_QUEUE_SIZE])
#define ovsrec_controller_col_controller_rate_limit (ovsrec_controller_columns[OVSREC_CONTROLLER_COL_CONTROLLER_RATE_LIMIT])
#define ovsrec_controller_col_enable_async_messages (ovsrec_controller_columns[OVSREC_CONTROLLER_COL_ENABLE_ASYNC_MESSAGES])
#define ovsrec_controller_col_external_ids (ovsrec_controller_columns[OVSREC_CONTROLLER_COL_EXTERNAL_IDS])
#define ovsrec_controller_col_inactivity_probe (ovsrec_controller_columns[OVSREC_CONTROLLER_COL_INACTIVITY_PROBE])
#define ovsrec_controller_col_is_connected (ovsrec_controller_columns[OVSREC_CONTROLLER_COL_IS_CONNECTED])
#define ovsrec_controller_col_local_gateway (ovsrec_controller_columns[OVSREC_CONTROLLER_COL_LOCAL_GATEWAY])
#define ovsrec_controller_col_local_ip (ovsrec_controller_columns[OVSREC_CONTROLLER_COL_LOCAL_IP])
#define ovsrec_controller_col_local_netmask (ovsrec_controller_columns[OVSREC_CONTROLLER_COL_LOCAL_NETMASK])
#define ovsrec_controller_col_max_backoff (ovsrec_controller_columns[OVSREC_CONTROLLER_COL_MAX_BACKOFF])
#define ovsrec_controller_col_other_config (ovsrec_controller_columns[OVSREC_CONTROLLER_COL_OTHER_CONFIG])
#define ovsrec_controller_col_role (ovsrec_controller_columns[OVSREC_CONTROLLER_COL_ROLE])
#define ovsrec_controller_col_status (ovsrec_controller_columns[OVSREC_CONTROLLER_COL_STATUS])
#define ovsrec_controller_col_target (ovsrec_controller_columns[OVSREC_CONTROLLER_COL_TARGET])
#define ovsrec_controller_col_type (ovsrec_controller_columns[OVSREC_CONTROLLER_COL_TYPE])

extern struct ovsdb_idl_column ovsrec_controller_columns[OVSREC_CONTROLLER_N_COLUMNS];
bool ovsrec_server_has_controller_table_col_connection_mode(const struct ovsdb_idl *); 
bool ovsrec_server_has_controller_table_col_controller_burst_limit(const struct ovsdb_idl *); 
bool ovsrec_server_has_controller_table_col_controller_queue_size(const struct ovsdb_idl *); 
bool ovsrec_server_has_controller_table_col_controller_rate_limit(const struct ovsdb_idl *); 
bool ovsrec_server_has_controller_table_col_enable_async_messages(const struct ovsdb_idl *); 
bool ovsrec_server_has_controller_table_col_external_ids(const struct ovsdb_idl *); 
bool ovsrec_server_has_controller_table_col_inactivity_probe(const struct ovsdb_idl *); 
bool ovsrec_server_has_controller_table_col_is_connected(const struct ovsdb_idl *); 
bool ovsrec_server_has_controller_table_col_local_gateway(const struct ovsdb_idl *); 
bool ovsrec_server_has_controller_table_col_local_ip(const struct ovsdb_idl *); 
bool ovsrec_server_has_controller_table_col_local_netmask(const struct ovsdb_idl *); 
bool ovsrec_server_has_controller_table_col_max_backoff(const struct ovsdb_idl *); 
bool ovsrec_server_has_controller_table_col_other_config(const struct ovsdb_idl *); 
bool ovsrec_server_has_controller_table_col_role(const struct ovsdb_idl *); 
bool ovsrec_server_has_controller_table_col_status(const struct ovsdb_idl *); 
bool ovsrec_server_has_controller_table_col_target(const struct ovsdb_idl *); 
bool ovsrec_server_has_controller_table_col_type(const struct ovsdb_idl *); 

bool ovsrec_server_has_controller_table(const struct ovsdb_idl *);
const struct ovsrec_controller_table *ovsrec_controller_table_get(const struct ovsdb_idl *);
const struct ovsrec_controller *ovsrec_controller_table_first(const struct ovsrec_controller_table *);

#define OVSREC_CONTROLLER_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_controller_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_controller_next(ROW))
#define OVSREC_CONTROLLER_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_controller_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_controller_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_CONTROLLER_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_controller * ROW__next = ((ROW) = ovsrec_controller_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_controller_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_CONTROLLER_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_CONTROLLER_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_CONTROLLER_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_controller *ovsrec_controller_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_controller *ovsrec_controller_table_get_for_uuid(const struct ovsrec_controller_table *, const struct uuid *);
const struct ovsrec_controller *ovsrec_controller_first(const struct ovsdb_idl *);
const struct ovsrec_controller *ovsrec_controller_next(const struct ovsrec_controller *);
#define OVSREC_CONTROLLER_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_controller_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_controller_next(ROW))
#define OVSREC_CONTROLLER_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_controller_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_controller_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_CONTROLLER_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_controller * ROW__next = ((ROW) = ovsrec_controller_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_controller_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_CONTROLLER_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_CONTROLLER_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_CONTROLLER_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_controller_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_controller_row_get_seqno(const struct ovsrec_controller *row, enum ovsdb_idl_change change);
const struct ovsrec_controller *ovsrec_controller_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_controller *ovsrec_controller_track_get_next(const struct ovsrec_controller *);
#define OVSREC_CONTROLLER_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_controller_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_controller_track_get_next(ROW))

const struct ovsrec_controller *ovsrec_controller_table_track_get_first(const struct ovsrec_controller_table *);
#define OVSREC_CONTROLLER_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_controller_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_controller_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_controller_is_new(const struct ovsrec_controller *row)
{
    return ovsrec_controller_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_controller_is_deleted(const struct ovsrec_controller *row)
{
    return ovsrec_controller_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_controller_index_destroy_row(const struct ovsrec_controller *);

struct ovsrec_controller *ovsrec_controller_index_find(struct ovsdb_idl_index *, const struct ovsrec_controller *);

int ovsrec_controller_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_controller *, 
    const struct ovsrec_controller *);
struct ovsdb_idl_cursor ovsrec_controller_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_controller_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_controller *);
struct ovsdb_idl_cursor ovsrec_controller_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_controller *);

struct ovsrec_controller *ovsrec_controller_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_CONTROLLER_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_controller_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_controller_cursor_data(&cursor__), \
                  !(TO) || ovsrec_controller_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_CONTROLLER_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_controller_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_controller_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_CONTROLLER_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_controller_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_controller_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_controller_init(struct ovsrec_controller *);
void ovsrec_controller_delete(const struct ovsrec_controller *);
struct ovsrec_controller *ovsrec_controller_insert(struct ovsdb_idl_txn *);
struct ovsrec_controller *ovsrec_controller_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_controller_column_id' of
 * the row referenced by 'struct ovsrec_controller *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_controller_is_updated(const struct ovsrec_controller *, enum ovsrec_controller_column_id);

void ovsrec_controller_verify_connection_mode(const struct ovsrec_controller *);
void ovsrec_controller_verify_controller_burst_limit(const struct ovsrec_controller *);
void ovsrec_controller_verify_controller_queue_size(const struct ovsrec_controller *);
void ovsrec_controller_verify_controller_rate_limit(const struct ovsrec_controller *);
void ovsrec_controller_verify_enable_async_messages(const struct ovsrec_controller *);
void ovsrec_controller_verify_external_ids(const struct ovsrec_controller *);
void ovsrec_controller_verify_inactivity_probe(const struct ovsrec_controller *);
void ovsrec_controller_verify_is_connected(const struct ovsrec_controller *);
void ovsrec_controller_verify_local_gateway(const struct ovsrec_controller *);
void ovsrec_controller_verify_local_ip(const struct ovsrec_controller *);
void ovsrec_controller_verify_local_netmask(const struct ovsrec_controller *);
void ovsrec_controller_verify_max_backoff(const struct ovsrec_controller *);
void ovsrec_controller_verify_other_config(const struct ovsrec_controller *);
void ovsrec_controller_verify_role(const struct ovsrec_controller *);
void ovsrec_controller_verify_status(const struct ovsrec_controller *);
void ovsrec_controller_verify_target(const struct ovsrec_controller *);
void ovsrec_controller_verify_type(const struct ovsrec_controller *);

const struct ovsdb_datum *ovsrec_controller_get_connection_mode(const struct ovsrec_controller *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_controller_get_controller_burst_limit(const struct ovsrec_controller *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_controller_get_controller_queue_size(const struct ovsrec_controller *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_controller_get_controller_rate_limit(const struct ovsrec_controller *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_controller_get_enable_async_messages(const struct ovsrec_controller *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_controller_get_external_ids(const struct ovsrec_controller *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_controller_get_inactivity_probe(const struct ovsrec_controller *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_controller_get_is_connected(const struct ovsrec_controller *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_controller_get_local_gateway(const struct ovsrec_controller *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_controller_get_local_ip(const struct ovsrec_controller *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_controller_get_local_netmask(const struct ovsrec_controller *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_controller_get_max_backoff(const struct ovsrec_controller *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_controller_get_other_config(const struct ovsrec_controller *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_controller_get_role(const struct ovsrec_controller *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_controller_get_status(const struct ovsrec_controller *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_controller_get_target(const struct ovsrec_controller *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_controller_get_type(const struct ovsrec_controller *, enum ovsdb_atomic_type key_type);

void ovsrec_controller_set_connection_mode(const struct ovsrec_controller *, const char *connection_mode);
void ovsrec_controller_set_controller_burst_limit(const struct ovsrec_controller *, const int64_t *controller_burst_limit, size_t n_controller_burst_limit);
void ovsrec_controller_set_controller_queue_size(const struct ovsrec_controller *, const int64_t *controller_queue_size, size_t n_controller_queue_size);
void ovsrec_controller_set_controller_rate_limit(const struct ovsrec_controller *, const int64_t *controller_rate_limit, size_t n_controller_rate_limit);
void ovsrec_controller_set_enable_async_messages(const struct ovsrec_controller *, const bool *enable_async_messages, size_t n_enable_async_messages);
void ovsrec_controller_set_external_ids(const struct ovsrec_controller *, const struct smap *);
void ovsrec_controller_set_inactivity_probe(const struct ovsrec_controller *, const int64_t *inactivity_probe, size_t n_inactivity_probe);
void ovsrec_controller_set_is_connected(const struct ovsrec_controller *, bool is_connected);
void ovsrec_controller_set_local_gateway(const struct ovsrec_controller *, const char *local_gateway);
void ovsrec_controller_set_local_ip(const struct ovsrec_controller *, const char *local_ip);
void ovsrec_controller_set_local_netmask(const struct ovsrec_controller *, const char *local_netmask);
void ovsrec_controller_set_max_backoff(const struct ovsrec_controller *, const int64_t *max_backoff, size_t n_max_backoff);
void ovsrec_controller_set_other_config(const struct ovsrec_controller *, const struct smap *);
void ovsrec_controller_set_role(const struct ovsrec_controller *, const char *role);
void ovsrec_controller_set_status(const struct ovsrec_controller *, const struct smap *);
void ovsrec_controller_set_target(const struct ovsrec_controller *, const char *target);
void ovsrec_controller_set_type(const struct ovsrec_controller *, const char *type);

void ovsrec_controller_update_connection_mode_addvalue(const struct ovsrec_controller *,  const char *);
void ovsrec_controller_update_connection_mode_delvalue(const struct ovsrec_controller *,  const char *);
void ovsrec_controller_add_clause_connection_mode(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *connection_mode);
unsigned int ovsrec_controller_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_controller_update_controller_burst_limit_addvalue(const struct ovsrec_controller *,  int64_t );
void ovsrec_controller_update_controller_burst_limit_delvalue(const struct ovsrec_controller *,  int64_t );
void ovsrec_controller_add_clause_controller_burst_limit(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *controller_burst_limit, size_t n_controller_burst_limit);
unsigned int ovsrec_controller_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_controller_update_controller_queue_size_addvalue(const struct ovsrec_controller *,  int64_t );
void ovsrec_controller_update_controller_queue_size_delvalue(const struct ovsrec_controller *,  int64_t );
void ovsrec_controller_add_clause_controller_queue_size(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *controller_queue_size, size_t n_controller_queue_size);
unsigned int ovsrec_controller_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_controller_update_controller_rate_limit_addvalue(const struct ovsrec_controller *,  int64_t );
void ovsrec_controller_update_controller_rate_limit_delvalue(const struct ovsrec_controller *,  int64_t );
void ovsrec_controller_add_clause_controller_rate_limit(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *controller_rate_limit, size_t n_controller_rate_limit);
unsigned int ovsrec_controller_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_controller_update_enable_async_messages_addvalue(const struct ovsrec_controller *,  bool );
void ovsrec_controller_update_enable_async_messages_delvalue(const struct ovsrec_controller *,  bool );
void ovsrec_controller_add_clause_enable_async_messages(struct ovsdb_idl_condition *, enum ovsdb_function function, const bool *enable_async_messages, size_t n_enable_async_messages);
unsigned int ovsrec_controller_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_controller_update_external_ids_setkey(const struct ovsrec_controller *,  const char *, const char *);
void ovsrec_controller_update_external_ids_delkey(const struct ovsrec_controller *,  const char *);
void ovsrec_controller_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_controller_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_controller_update_inactivity_probe_addvalue(const struct ovsrec_controller *,  int64_t );
void ovsrec_controller_update_inactivity_probe_delvalue(const struct ovsrec_controller *,  int64_t );
void ovsrec_controller_add_clause_inactivity_probe(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *inactivity_probe, size_t n_inactivity_probe);
unsigned int ovsrec_controller_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_controller_add_clause_is_connected(struct ovsdb_idl_condition *, enum ovsdb_function function, bool is_connected);
unsigned int ovsrec_controller_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_controller_update_local_gateway_addvalue(const struct ovsrec_controller *,  const char *);
void ovsrec_controller_update_local_gateway_delvalue(const struct ovsrec_controller *,  const char *);
void ovsrec_controller_add_clause_local_gateway(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *local_gateway);
unsigned int ovsrec_controller_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_controller_update_local_ip_addvalue(const struct ovsrec_controller *,  const char *);
void ovsrec_controller_update_local_ip_delvalue(const struct ovsrec_controller *,  const char *);
void ovsrec_controller_add_clause_local_ip(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *local_ip);
unsigned int ovsrec_controller_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_controller_update_local_netmask_addvalue(const struct ovsrec_controller *,  const char *);
void ovsrec_controller_update_local_netmask_delvalue(const struct ovsrec_controller *,  const char *);
void ovsrec_controller_add_clause_local_netmask(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *local_netmask);
unsigned int ovsrec_controller_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_controller_update_max_backoff_addvalue(const struct ovsrec_controller *,  int64_t );
void ovsrec_controller_update_max_backoff_delvalue(const struct ovsrec_controller *,  int64_t );
void ovsrec_controller_add_clause_max_backoff(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *max_backoff, size_t n_max_backoff);
unsigned int ovsrec_controller_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_controller_update_other_config_setkey(const struct ovsrec_controller *,  const char *, const char *);
void ovsrec_controller_update_other_config_delkey(const struct ovsrec_controller *,  const char *);
void ovsrec_controller_add_clause_other_config(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_controller_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_controller_update_role_addvalue(const struct ovsrec_controller *,  const char *);
void ovsrec_controller_update_role_delvalue(const struct ovsrec_controller *,  const char *);
void ovsrec_controller_add_clause_role(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *role);
unsigned int ovsrec_controller_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_controller_update_status_setkey(const struct ovsrec_controller *,  const char *, const char *);
void ovsrec_controller_update_status_delkey(const struct ovsrec_controller *,  const char *);
void ovsrec_controller_add_clause_status(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_controller_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_controller_add_clause_target(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *target);
unsigned int ovsrec_controller_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_controller_update_type_addvalue(const struct ovsrec_controller *,  const char *);
void ovsrec_controller_update_type_delvalue(const struct ovsrec_controller *,  const char *);
void ovsrec_controller_add_clause_type(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *type);
unsigned int ovsrec_controller_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_controller *ovsrec_controller_index_init_row(struct ovsdb_idl_index *);
void ovsrec_controller_index_set_connection_mode(const struct ovsrec_controller *,
const char *connection_mode);
void ovsrec_controller_index_set_controller_burst_limit(const struct ovsrec_controller *,
const int64_t *controller_burst_limit, size_t n_controller_burst_limit);
void ovsrec_controller_index_set_controller_queue_size(const struct ovsrec_controller *,
const int64_t *controller_queue_size, size_t n_controller_queue_size);
void ovsrec_controller_index_set_controller_rate_limit(const struct ovsrec_controller *,
const int64_t *controller_rate_limit, size_t n_controller_rate_limit);
void ovsrec_controller_index_set_enable_async_messages(const struct ovsrec_controller *,
const bool *enable_async_messages, size_t n_enable_async_messages);
void ovsrec_controller_index_set_external_ids(const struct ovsrec_controller *,
const struct smap *);
void ovsrec_controller_index_set_inactivity_probe(const struct ovsrec_controller *,
const int64_t *inactivity_probe, size_t n_inactivity_probe);
void ovsrec_controller_index_set_is_connected(const struct ovsrec_controller *,
bool is_connected);
void ovsrec_controller_index_set_local_gateway(const struct ovsrec_controller *,
const char *local_gateway);
void ovsrec_controller_index_set_local_ip(const struct ovsrec_controller *,
const char *local_ip);
void ovsrec_controller_index_set_local_netmask(const struct ovsrec_controller *,
const char *local_netmask);
void ovsrec_controller_index_set_max_backoff(const struct ovsrec_controller *,
const int64_t *max_backoff, size_t n_max_backoff);
void ovsrec_controller_index_set_other_config(const struct ovsrec_controller *,
const struct smap *);
void ovsrec_controller_index_set_role(const struct ovsrec_controller *,
const char *role);
void ovsrec_controller_index_set_status(const struct ovsrec_controller *,
const struct smap *);
void ovsrec_controller_index_set_target(const struct ovsrec_controller *,
const char *target);
void ovsrec_controller_index_set_type(const struct ovsrec_controller *,
const char *type);

/* Datapath table. */
struct ovsrec_datapath {
	struct ovsdb_idl_row header_;

	/* capabilities column. */
	struct smap capabilities;

	/* ct_zones column. */
	int64_t *key_ct_zones;
	struct ovsrec_ct_zone **value_ct_zones;
	size_t n_ct_zones;

	/* datapath_version column. */
	char *datapath_version;	/* Always nonnull. */

	/* external_ids column. */
	struct smap external_ids;
};

enum ovsrec_datapath_column_id {
    OVSREC_DATAPATH_COL_CAPABILITIES,
    OVSREC_DATAPATH_COL_CT_ZONES,
    OVSREC_DATAPATH_COL_DATAPATH_VERSION,
    OVSREC_DATAPATH_COL_EXTERNAL_IDS,
    OVSREC_DATAPATH_N_COLUMNS
};

#define ovsrec_datapath_col_capabilities (ovsrec_datapath_columns[OVSREC_DATAPATH_COL_CAPABILITIES])
#define ovsrec_datapath_col_ct_zones (ovsrec_datapath_columns[OVSREC_DATAPATH_COL_CT_ZONES])
#define ovsrec_datapath_col_datapath_version (ovsrec_datapath_columns[OVSREC_DATAPATH_COL_DATAPATH_VERSION])
#define ovsrec_datapath_col_external_ids (ovsrec_datapath_columns[OVSREC_DATAPATH_COL_EXTERNAL_IDS])

extern struct ovsdb_idl_column ovsrec_datapath_columns[OVSREC_DATAPATH_N_COLUMNS];
bool ovsrec_server_has_datapath_table_col_capabilities(const struct ovsdb_idl *); 
bool ovsrec_server_has_datapath_table_col_ct_zones(const struct ovsdb_idl *); 
bool ovsrec_server_has_datapath_table_col_datapath_version(const struct ovsdb_idl *); 
bool ovsrec_server_has_datapath_table_col_external_ids(const struct ovsdb_idl *); 

bool ovsrec_server_has_datapath_table(const struct ovsdb_idl *);
const struct ovsrec_datapath_table *ovsrec_datapath_table_get(const struct ovsdb_idl *);
const struct ovsrec_datapath *ovsrec_datapath_table_first(const struct ovsrec_datapath_table *);

#define OVSREC_DATAPATH_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_datapath_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_datapath_next(ROW))
#define OVSREC_DATAPATH_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_datapath_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_datapath_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_DATAPATH_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_datapath * ROW__next = ((ROW) = ovsrec_datapath_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_datapath_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_DATAPATH_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_DATAPATH_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_DATAPATH_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_datapath *ovsrec_datapath_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_datapath *ovsrec_datapath_table_get_for_uuid(const struct ovsrec_datapath_table *, const struct uuid *);
const struct ovsrec_datapath *ovsrec_datapath_first(const struct ovsdb_idl *);
const struct ovsrec_datapath *ovsrec_datapath_next(const struct ovsrec_datapath *);
#define OVSREC_DATAPATH_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_datapath_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_datapath_next(ROW))
#define OVSREC_DATAPATH_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_datapath_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_datapath_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_DATAPATH_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_datapath * ROW__next = ((ROW) = ovsrec_datapath_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_datapath_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_DATAPATH_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_DATAPATH_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_DATAPATH_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_datapath_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_datapath_row_get_seqno(const struct ovsrec_datapath *row, enum ovsdb_idl_change change);
const struct ovsrec_datapath *ovsrec_datapath_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_datapath *ovsrec_datapath_track_get_next(const struct ovsrec_datapath *);
#define OVSREC_DATAPATH_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_datapath_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_datapath_track_get_next(ROW))

const struct ovsrec_datapath *ovsrec_datapath_table_track_get_first(const struct ovsrec_datapath_table *);
#define OVSREC_DATAPATH_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_datapath_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_datapath_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_datapath_is_new(const struct ovsrec_datapath *row)
{
    return ovsrec_datapath_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_datapath_is_deleted(const struct ovsrec_datapath *row)
{
    return ovsrec_datapath_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_datapath_index_destroy_row(const struct ovsrec_datapath *);

struct ovsrec_datapath *ovsrec_datapath_index_find(struct ovsdb_idl_index *, const struct ovsrec_datapath *);

int ovsrec_datapath_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_datapath *, 
    const struct ovsrec_datapath *);
struct ovsdb_idl_cursor ovsrec_datapath_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_datapath_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_datapath *);
struct ovsdb_idl_cursor ovsrec_datapath_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_datapath *);

struct ovsrec_datapath *ovsrec_datapath_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_DATAPATH_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_datapath_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_datapath_cursor_data(&cursor__), \
                  !(TO) || ovsrec_datapath_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_DATAPATH_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_datapath_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_datapath_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_DATAPATH_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_datapath_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_datapath_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_datapath_init(struct ovsrec_datapath *);
void ovsrec_datapath_delete(const struct ovsrec_datapath *);
struct ovsrec_datapath *ovsrec_datapath_insert(struct ovsdb_idl_txn *);
struct ovsrec_datapath *ovsrec_datapath_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_datapath_column_id' of
 * the row referenced by 'struct ovsrec_datapath *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_datapath_is_updated(const struct ovsrec_datapath *, enum ovsrec_datapath_column_id);

void ovsrec_datapath_verify_capabilities(const struct ovsrec_datapath *);
void ovsrec_datapath_verify_ct_zones(const struct ovsrec_datapath *);
void ovsrec_datapath_verify_datapath_version(const struct ovsrec_datapath *);
void ovsrec_datapath_verify_external_ids(const struct ovsrec_datapath *);

const struct ovsdb_datum *ovsrec_datapath_get_capabilities(const struct ovsrec_datapath *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_datapath_get_ct_zones(const struct ovsrec_datapath *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_datapath_get_datapath_version(const struct ovsrec_datapath *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_datapath_get_external_ids(const struct ovsrec_datapath *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);

void ovsrec_datapath_set_capabilities(const struct ovsrec_datapath *, const struct smap *);
void ovsrec_datapath_set_ct_zones(const struct ovsrec_datapath *, const int64_t *key_ct_zones, struct ovsrec_ct_zone **value_ct_zones, size_t n_ct_zones);
void ovsrec_datapath_set_datapath_version(const struct ovsrec_datapath *, const char *datapath_version);
void ovsrec_datapath_set_external_ids(const struct ovsrec_datapath *, const struct smap *);

void ovsrec_datapath_update_capabilities_setkey(const struct ovsrec_datapath *,  const char *, const char *);
void ovsrec_datapath_update_capabilities_delkey(const struct ovsrec_datapath *,  const char *);
void ovsrec_datapath_add_clause_capabilities(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_datapath_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_datapath_update_ct_zones_setkey(const struct ovsrec_datapath *,  int64_t , const struct ovsrec_ct_zone *);
void ovsrec_datapath_update_ct_zones_delkey(const struct ovsrec_datapath *,  int64_t );
void ovsrec_datapath_add_clause_ct_zones(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *key_ct_zones, struct uuid **value_ct_zones, size_t n_ct_zones);
unsigned int ovsrec_datapath_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_datapath_add_clause_datapath_version(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *datapath_version);
unsigned int ovsrec_datapath_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_datapath_update_external_ids_setkey(const struct ovsrec_datapath *,  const char *, const char *);
void ovsrec_datapath_update_external_ids_delkey(const struct ovsrec_datapath *,  const char *);
void ovsrec_datapath_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_datapath_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_datapath *ovsrec_datapath_index_init_row(struct ovsdb_idl_index *);
void ovsrec_datapath_index_set_capabilities(const struct ovsrec_datapath *,
const struct smap *);
void ovsrec_datapath_index_set_ct_zones(const struct ovsrec_datapath *,
const int64_t *key_ct_zones, struct ovsrec_ct_zone **value_ct_zones, size_t n_ct_zones);
void ovsrec_datapath_index_set_datapath_version(const struct ovsrec_datapath *,
const char *datapath_version);
void ovsrec_datapath_index_set_external_ids(const struct ovsrec_datapath *,
const struct smap *);

/* Flow_Sample_Collector_Set table. */
struct ovsrec_flow_sample_collector_set {
	struct ovsdb_idl_row header_;

	/* bridge column. */
	struct ovsrec_bridge *bridge;

	/* external_ids column. */
	struct smap external_ids;

	/* id column. */
	int64_t id;

	/* ipfix column. */
	struct ovsrec_ipfix *ipfix;
};

enum ovsrec_flow_sample_collector_set_column_id {
    OVSREC_FLOW_SAMPLE_COLLECTOR_SET_COL_BRIDGE,
    OVSREC_FLOW_SAMPLE_COLLECTOR_SET_COL_EXTERNAL_IDS,
    OVSREC_FLOW_SAMPLE_COLLECTOR_SET_COL_ID,
    OVSREC_FLOW_SAMPLE_COLLECTOR_SET_COL_IPFIX,
    OVSREC_FLOW_SAMPLE_COLLECTOR_SET_N_COLUMNS
};

#define ovsrec_flow_sample_collector_set_col_bridge (ovsrec_flow_sample_collector_set_columns[OVSREC_FLOW_SAMPLE_COLLECTOR_SET_COL_BRIDGE])
#define ovsrec_flow_sample_collector_set_col_external_ids (ovsrec_flow_sample_collector_set_columns[OVSREC_FLOW_SAMPLE_COLLECTOR_SET_COL_EXTERNAL_IDS])
#define ovsrec_flow_sample_collector_set_col_id (ovsrec_flow_sample_collector_set_columns[OVSREC_FLOW_SAMPLE_COLLECTOR_SET_COL_ID])
#define ovsrec_flow_sample_collector_set_col_ipfix (ovsrec_flow_sample_collector_set_columns[OVSREC_FLOW_SAMPLE_COLLECTOR_SET_COL_IPFIX])

extern struct ovsdb_idl_column ovsrec_flow_sample_collector_set_columns[OVSREC_FLOW_SAMPLE_COLLECTOR_SET_N_COLUMNS];
bool ovsrec_server_has_flow_sample_collector_set_table_col_bridge(const struct ovsdb_idl *); 
bool ovsrec_server_has_flow_sample_collector_set_table_col_external_ids(const struct ovsdb_idl *); 
bool ovsrec_server_has_flow_sample_collector_set_table_col_id(const struct ovsdb_idl *); 
bool ovsrec_server_has_flow_sample_collector_set_table_col_ipfix(const struct ovsdb_idl *); 

bool ovsrec_server_has_flow_sample_collector_set_table(const struct ovsdb_idl *);
const struct ovsrec_flow_sample_collector_set_table *ovsrec_flow_sample_collector_set_table_get(const struct ovsdb_idl *);
const struct ovsrec_flow_sample_collector_set *ovsrec_flow_sample_collector_set_table_first(const struct ovsrec_flow_sample_collector_set_table *);

#define OVSREC_FLOW_SAMPLE_COLLECTOR_SET_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_flow_sample_collector_set_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_flow_sample_collector_set_next(ROW))
#define OVSREC_FLOW_SAMPLE_COLLECTOR_SET_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_flow_sample_collector_set_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_flow_sample_collector_set_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_FLOW_SAMPLE_COLLECTOR_SET_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_flow_sample_collector_set * ROW__next = ((ROW) = ovsrec_flow_sample_collector_set_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_flow_sample_collector_set_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_FLOW_SAMPLE_COLLECTOR_SET_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_FLOW_SAMPLE_COLLECTOR_SET_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_FLOW_SAMPLE_COLLECTOR_SET_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_flow_sample_collector_set *ovsrec_flow_sample_collector_set_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_flow_sample_collector_set *ovsrec_flow_sample_collector_set_table_get_for_uuid(const struct ovsrec_flow_sample_collector_set_table *, const struct uuid *);
const struct ovsrec_flow_sample_collector_set *ovsrec_flow_sample_collector_set_first(const struct ovsdb_idl *);
const struct ovsrec_flow_sample_collector_set *ovsrec_flow_sample_collector_set_next(const struct ovsrec_flow_sample_collector_set *);
#define OVSREC_FLOW_SAMPLE_COLLECTOR_SET_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_flow_sample_collector_set_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_flow_sample_collector_set_next(ROW))
#define OVSREC_FLOW_SAMPLE_COLLECTOR_SET_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_flow_sample_collector_set_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_flow_sample_collector_set_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_FLOW_SAMPLE_COLLECTOR_SET_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_flow_sample_collector_set * ROW__next = ((ROW) = ovsrec_flow_sample_collector_set_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_flow_sample_collector_set_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_FLOW_SAMPLE_COLLECTOR_SET_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_FLOW_SAMPLE_COLLECTOR_SET_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_FLOW_SAMPLE_COLLECTOR_SET_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_flow_sample_collector_set_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_flow_sample_collector_set_row_get_seqno(const struct ovsrec_flow_sample_collector_set *row, enum ovsdb_idl_change change);
const struct ovsrec_flow_sample_collector_set *ovsrec_flow_sample_collector_set_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_flow_sample_collector_set *ovsrec_flow_sample_collector_set_track_get_next(const struct ovsrec_flow_sample_collector_set *);
#define OVSREC_FLOW_SAMPLE_COLLECTOR_SET_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_flow_sample_collector_set_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_flow_sample_collector_set_track_get_next(ROW))

const struct ovsrec_flow_sample_collector_set *ovsrec_flow_sample_collector_set_table_track_get_first(const struct ovsrec_flow_sample_collector_set_table *);
#define OVSREC_FLOW_SAMPLE_COLLECTOR_SET_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_flow_sample_collector_set_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_flow_sample_collector_set_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_flow_sample_collector_set_is_new(const struct ovsrec_flow_sample_collector_set *row)
{
    return ovsrec_flow_sample_collector_set_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_flow_sample_collector_set_is_deleted(const struct ovsrec_flow_sample_collector_set *row)
{
    return ovsrec_flow_sample_collector_set_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_flow_sample_collector_set_index_destroy_row(const struct ovsrec_flow_sample_collector_set *);

struct ovsrec_flow_sample_collector_set *ovsrec_flow_sample_collector_set_index_find(struct ovsdb_idl_index *, const struct ovsrec_flow_sample_collector_set *);

int ovsrec_flow_sample_collector_set_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_flow_sample_collector_set *, 
    const struct ovsrec_flow_sample_collector_set *);
struct ovsdb_idl_cursor ovsrec_flow_sample_collector_set_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_flow_sample_collector_set_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_flow_sample_collector_set *);
struct ovsdb_idl_cursor ovsrec_flow_sample_collector_set_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_flow_sample_collector_set *);

struct ovsrec_flow_sample_collector_set *ovsrec_flow_sample_collector_set_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_FLOW_SAMPLE_COLLECTOR_SET_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_flow_sample_collector_set_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_flow_sample_collector_set_cursor_data(&cursor__), \
                  !(TO) || ovsrec_flow_sample_collector_set_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_FLOW_SAMPLE_COLLECTOR_SET_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_flow_sample_collector_set_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_flow_sample_collector_set_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_FLOW_SAMPLE_COLLECTOR_SET_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_flow_sample_collector_set_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_flow_sample_collector_set_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_flow_sample_collector_set_init(struct ovsrec_flow_sample_collector_set *);
void ovsrec_flow_sample_collector_set_delete(const struct ovsrec_flow_sample_collector_set *);
struct ovsrec_flow_sample_collector_set *ovsrec_flow_sample_collector_set_insert(struct ovsdb_idl_txn *);
struct ovsrec_flow_sample_collector_set *ovsrec_flow_sample_collector_set_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_flow_sample_collector_set_column_id' of
 * the row referenced by 'struct ovsrec_flow_sample_collector_set *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_flow_sample_collector_set_is_updated(const struct ovsrec_flow_sample_collector_set *, enum ovsrec_flow_sample_collector_set_column_id);

void ovsrec_flow_sample_collector_set_verify_bridge(const struct ovsrec_flow_sample_collector_set *);
void ovsrec_flow_sample_collector_set_verify_external_ids(const struct ovsrec_flow_sample_collector_set *);
void ovsrec_flow_sample_collector_set_verify_id(const struct ovsrec_flow_sample_collector_set *);
void ovsrec_flow_sample_collector_set_verify_ipfix(const struct ovsrec_flow_sample_collector_set *);

const struct ovsdb_datum *ovsrec_flow_sample_collector_set_get_bridge(const struct ovsrec_flow_sample_collector_set *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_flow_sample_collector_set_get_external_ids(const struct ovsrec_flow_sample_collector_set *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_flow_sample_collector_set_get_id(const struct ovsrec_flow_sample_collector_set *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_flow_sample_collector_set_get_ipfix(const struct ovsrec_flow_sample_collector_set *, enum ovsdb_atomic_type key_type);

void ovsrec_flow_sample_collector_set_set_bridge(const struct ovsrec_flow_sample_collector_set *, const struct ovsrec_bridge *bridge);
void ovsrec_flow_sample_collector_set_set_external_ids(const struct ovsrec_flow_sample_collector_set *, const struct smap *);
void ovsrec_flow_sample_collector_set_set_id(const struct ovsrec_flow_sample_collector_set *, int64_t id);
void ovsrec_flow_sample_collector_set_set_ipfix(const struct ovsrec_flow_sample_collector_set *, const struct ovsrec_ipfix *ipfix);

void ovsrec_flow_sample_collector_set_add_clause_bridge(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct uuid *bridge);
unsigned int ovsrec_flow_sample_collector_set_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_flow_sample_collector_set_update_external_ids_setkey(const struct ovsrec_flow_sample_collector_set *,  const char *, const char *);
void ovsrec_flow_sample_collector_set_update_external_ids_delkey(const struct ovsrec_flow_sample_collector_set *,  const char *);
void ovsrec_flow_sample_collector_set_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_flow_sample_collector_set_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_flow_sample_collector_set_add_clause_id(struct ovsdb_idl_condition *, enum ovsdb_function function, int64_t id);
unsigned int ovsrec_flow_sample_collector_set_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_flow_sample_collector_set_update_ipfix_addvalue(const struct ovsrec_flow_sample_collector_set *,  const struct ovsrec_ipfix *);
void ovsrec_flow_sample_collector_set_update_ipfix_delvalue(const struct ovsrec_flow_sample_collector_set *,  const struct ovsrec_ipfix *);
void ovsrec_flow_sample_collector_set_add_clause_ipfix(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct uuid *ipfix);
unsigned int ovsrec_flow_sample_collector_set_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_flow_sample_collector_set *ovsrec_flow_sample_collector_set_index_init_row(struct ovsdb_idl_index *);
void ovsrec_flow_sample_collector_set_index_set_bridge(const struct ovsrec_flow_sample_collector_set *,
const struct ovsrec_bridge *bridge);
void ovsrec_flow_sample_collector_set_index_set_external_ids(const struct ovsrec_flow_sample_collector_set *,
const struct smap *);
void ovsrec_flow_sample_collector_set_index_set_id(const struct ovsrec_flow_sample_collector_set *,
int64_t id);
void ovsrec_flow_sample_collector_set_index_set_ipfix(const struct ovsrec_flow_sample_collector_set *,
const struct ovsrec_ipfix *ipfix);

/* Flow_Table table. */
struct ovsrec_flow_table {
	struct ovsdb_idl_row header_;

	/* external_ids column. */
	struct smap external_ids;

	/* flow_limit column. */
	int64_t *flow_limit;
	size_t n_flow_limit;

	/* groups column. */
	char **groups;
	size_t n_groups;

	/* name column. */
	char *name;

	/* overflow_policy column. */
	char *overflow_policy;

	/* prefixes column. */
	char **prefixes;
	size_t n_prefixes;
};

enum ovsrec_flow_table_column_id {
    OVSREC_FLOW_TABLE_COL_EXTERNAL_IDS,
    OVSREC_FLOW_TABLE_COL_FLOW_LIMIT,
    OVSREC_FLOW_TABLE_COL_GROUPS,
    OVSREC_FLOW_TABLE_COL_NAME,
    OVSREC_FLOW_TABLE_COL_OVERFLOW_POLICY,
    OVSREC_FLOW_TABLE_COL_PREFIXES,
    OVSREC_FLOW_TABLE_N_COLUMNS
};

#define ovsrec_flow_table_col_external_ids (ovsrec_flow_table_columns[OVSREC_FLOW_TABLE_COL_EXTERNAL_IDS])
#define ovsrec_flow_table_col_flow_limit (ovsrec_flow_table_columns[OVSREC_FLOW_TABLE_COL_FLOW_LIMIT])
#define ovsrec_flow_table_col_groups (ovsrec_flow_table_columns[OVSREC_FLOW_TABLE_COL_GROUPS])
#define ovsrec_flow_table_col_name (ovsrec_flow_table_columns[OVSREC_FLOW_TABLE_COL_NAME])
#define ovsrec_flow_table_col_overflow_policy (ovsrec_flow_table_columns[OVSREC_FLOW_TABLE_COL_OVERFLOW_POLICY])
#define ovsrec_flow_table_col_prefixes (ovsrec_flow_table_columns[OVSREC_FLOW_TABLE_COL_PREFIXES])

extern struct ovsdb_idl_column ovsrec_flow_table_columns[OVSREC_FLOW_TABLE_N_COLUMNS];
bool ovsrec_server_has_flow_table_table_col_external_ids(const struct ovsdb_idl *); 
bool ovsrec_server_has_flow_table_table_col_flow_limit(const struct ovsdb_idl *); 
bool ovsrec_server_has_flow_table_table_col_groups(const struct ovsdb_idl *); 
bool ovsrec_server_has_flow_table_table_col_name(const struct ovsdb_idl *); 
bool ovsrec_server_has_flow_table_table_col_overflow_policy(const struct ovsdb_idl *); 
bool ovsrec_server_has_flow_table_table_col_prefixes(const struct ovsdb_idl *); 

bool ovsrec_server_has_flow_table_table(const struct ovsdb_idl *);
const struct ovsrec_flow_table_table *ovsrec_flow_table_table_get(const struct ovsdb_idl *);
const struct ovsrec_flow_table *ovsrec_flow_table_table_first(const struct ovsrec_flow_table_table *);

#define OVSREC_FLOW_TABLE_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_flow_table_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_flow_table_next(ROW))
#define OVSREC_FLOW_TABLE_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_flow_table_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_flow_table_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_FLOW_TABLE_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_flow_table * ROW__next = ((ROW) = ovsrec_flow_table_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_flow_table_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_FLOW_TABLE_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_FLOW_TABLE_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_FLOW_TABLE_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_flow_table *ovsrec_flow_table_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_flow_table *ovsrec_flow_table_table_get_for_uuid(const struct ovsrec_flow_table_table *, const struct uuid *);
const struct ovsrec_flow_table *ovsrec_flow_table_first(const struct ovsdb_idl *);
const struct ovsrec_flow_table *ovsrec_flow_table_next(const struct ovsrec_flow_table *);
#define OVSREC_FLOW_TABLE_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_flow_table_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_flow_table_next(ROW))
#define OVSREC_FLOW_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_flow_table_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_flow_table_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_FLOW_TABLE_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_flow_table * ROW__next = ((ROW) = ovsrec_flow_table_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_flow_table_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_FLOW_TABLE_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_FLOW_TABLE_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_FLOW_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_flow_table_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_flow_table_row_get_seqno(const struct ovsrec_flow_table *row, enum ovsdb_idl_change change);
const struct ovsrec_flow_table *ovsrec_flow_table_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_flow_table *ovsrec_flow_table_track_get_next(const struct ovsrec_flow_table *);
#define OVSREC_FLOW_TABLE_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_flow_table_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_flow_table_track_get_next(ROW))

const struct ovsrec_flow_table *ovsrec_flow_table_table_track_get_first(const struct ovsrec_flow_table_table *);
#define OVSREC_FLOW_TABLE_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_flow_table_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_flow_table_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_flow_table_is_new(const struct ovsrec_flow_table *row)
{
    return ovsrec_flow_table_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_flow_table_is_deleted(const struct ovsrec_flow_table *row)
{
    return ovsrec_flow_table_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_flow_table_index_destroy_row(const struct ovsrec_flow_table *);

struct ovsrec_flow_table *ovsrec_flow_table_index_find(struct ovsdb_idl_index *, const struct ovsrec_flow_table *);

int ovsrec_flow_table_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_flow_table *, 
    const struct ovsrec_flow_table *);
struct ovsdb_idl_cursor ovsrec_flow_table_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_flow_table_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_flow_table *);
struct ovsdb_idl_cursor ovsrec_flow_table_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_flow_table *);

struct ovsrec_flow_table *ovsrec_flow_table_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_FLOW_TABLE_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_flow_table_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_flow_table_cursor_data(&cursor__), \
                  !(TO) || ovsrec_flow_table_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_FLOW_TABLE_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_flow_table_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_flow_table_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_FLOW_TABLE_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_flow_table_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_flow_table_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_flow_table_init(struct ovsrec_flow_table *);
void ovsrec_flow_table_delete(const struct ovsrec_flow_table *);
struct ovsrec_flow_table *ovsrec_flow_table_insert(struct ovsdb_idl_txn *);
struct ovsrec_flow_table *ovsrec_flow_table_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_flow_table_column_id' of
 * the row referenced by 'struct ovsrec_flow_table *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_flow_table_is_updated(const struct ovsrec_flow_table *, enum ovsrec_flow_table_column_id);

void ovsrec_flow_table_verify_external_ids(const struct ovsrec_flow_table *);
void ovsrec_flow_table_verify_flow_limit(const struct ovsrec_flow_table *);
void ovsrec_flow_table_verify_groups(const struct ovsrec_flow_table *);
void ovsrec_flow_table_verify_name(const struct ovsrec_flow_table *);
void ovsrec_flow_table_verify_overflow_policy(const struct ovsrec_flow_table *);
void ovsrec_flow_table_verify_prefixes(const struct ovsrec_flow_table *);

const struct ovsdb_datum *ovsrec_flow_table_get_external_ids(const struct ovsrec_flow_table *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_flow_table_get_flow_limit(const struct ovsrec_flow_table *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_flow_table_get_groups(const struct ovsrec_flow_table *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_flow_table_get_name(const struct ovsrec_flow_table *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_flow_table_get_overflow_policy(const struct ovsrec_flow_table *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_flow_table_get_prefixes(const struct ovsrec_flow_table *, enum ovsdb_atomic_type key_type);

void ovsrec_flow_table_set_external_ids(const struct ovsrec_flow_table *, const struct smap *);
void ovsrec_flow_table_set_flow_limit(const struct ovsrec_flow_table *, const int64_t *flow_limit, size_t n_flow_limit);
void ovsrec_flow_table_set_groups(const struct ovsrec_flow_table *, const char **groups, size_t n_groups);
void ovsrec_flow_table_set_name(const struct ovsrec_flow_table *, const char *name);
void ovsrec_flow_table_set_overflow_policy(const struct ovsrec_flow_table *, const char *overflow_policy);
void ovsrec_flow_table_set_prefixes(const struct ovsrec_flow_table *, const char **prefixes, size_t n_prefixes);

void ovsrec_flow_table_update_external_ids_setkey(const struct ovsrec_flow_table *,  const char *, const char *);
void ovsrec_flow_table_update_external_ids_delkey(const struct ovsrec_flow_table *,  const char *);
void ovsrec_flow_table_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_flow_table_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_flow_table_update_flow_limit_addvalue(const struct ovsrec_flow_table *,  int64_t );
void ovsrec_flow_table_update_flow_limit_delvalue(const struct ovsrec_flow_table *,  int64_t );
void ovsrec_flow_table_add_clause_flow_limit(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *flow_limit, size_t n_flow_limit);
unsigned int ovsrec_flow_table_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_flow_table_update_groups_addvalue(const struct ovsrec_flow_table *,  const char *);
void ovsrec_flow_table_update_groups_delvalue(const struct ovsrec_flow_table *,  const char *);
void ovsrec_flow_table_add_clause_groups(struct ovsdb_idl_condition *, enum ovsdb_function function, const char **groups, size_t n_groups);
unsigned int ovsrec_flow_table_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_flow_table_update_name_addvalue(const struct ovsrec_flow_table *,  const char *);
void ovsrec_flow_table_update_name_delvalue(const struct ovsrec_flow_table *,  const char *);
void ovsrec_flow_table_add_clause_name(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *name);
unsigned int ovsrec_flow_table_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_flow_table_update_overflow_policy_addvalue(const struct ovsrec_flow_table *,  const char *);
void ovsrec_flow_table_update_overflow_policy_delvalue(const struct ovsrec_flow_table *,  const char *);
void ovsrec_flow_table_add_clause_overflow_policy(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *overflow_policy);
unsigned int ovsrec_flow_table_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_flow_table_update_prefixes_addvalue(const struct ovsrec_flow_table *,  const char *);
void ovsrec_flow_table_update_prefixes_delvalue(const struct ovsrec_flow_table *,  const char *);
void ovsrec_flow_table_add_clause_prefixes(struct ovsdb_idl_condition *, enum ovsdb_function function, const char **prefixes, size_t n_prefixes);
unsigned int ovsrec_flow_table_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_flow_table *ovsrec_flow_table_index_init_row(struct ovsdb_idl_index *);
void ovsrec_flow_table_index_set_external_ids(const struct ovsrec_flow_table *,
const struct smap *);
void ovsrec_flow_table_index_set_flow_limit(const struct ovsrec_flow_table *,
const int64_t *flow_limit, size_t n_flow_limit);
void ovsrec_flow_table_index_set_groups(const struct ovsrec_flow_table *,
const char **groups, size_t n_groups);
void ovsrec_flow_table_index_set_name(const struct ovsrec_flow_table *,
const char *name);
void ovsrec_flow_table_index_set_overflow_policy(const struct ovsrec_flow_table *,
const char *overflow_policy);
void ovsrec_flow_table_index_set_prefixes(const struct ovsrec_flow_table *,
const char **prefixes, size_t n_prefixes);

/* IPFIX table. */
struct ovsrec_ipfix {
	struct ovsdb_idl_row header_;

	/* cache_active_timeout column. */
	int64_t *cache_active_timeout;
	size_t n_cache_active_timeout;

	/* cache_max_flows column. */
	int64_t *cache_max_flows;
	size_t n_cache_max_flows;

	/* external_ids column. */
	struct smap external_ids;

	/* obs_domain_id column. */
	int64_t *obs_domain_id;
	size_t n_obs_domain_id;

	/* obs_point_id column. */
	int64_t *obs_point_id;
	size_t n_obs_point_id;

	/* other_config column. */
	struct smap other_config;

	/* sampling column. */
	int64_t *sampling;
	size_t n_sampling;

	/* targets column. */
	char **targets;
	size_t n_targets;
};

enum ovsrec_ipfix_column_id {
    OVSREC_IPFIX_COL_CACHE_ACTIVE_TIMEOUT,
    OVSREC_IPFIX_COL_CACHE_MAX_FLOWS,
    OVSREC_IPFIX_COL_EXTERNAL_IDS,
    OVSREC_IPFIX_COL_OBS_DOMAIN_ID,
    OVSREC_IPFIX_COL_OBS_POINT_ID,
    OVSREC_IPFIX_COL_OTHER_CONFIG,
    OVSREC_IPFIX_COL_SAMPLING,
    OVSREC_IPFIX_COL_TARGETS,
    OVSREC_IPFIX_N_COLUMNS
};

#define ovsrec_ipfix_col_cache_active_timeout (ovsrec_ipfix_columns[OVSREC_IPFIX_COL_CACHE_ACTIVE_TIMEOUT])
#define ovsrec_ipfix_col_cache_max_flows (ovsrec_ipfix_columns[OVSREC_IPFIX_COL_CACHE_MAX_FLOWS])
#define ovsrec_ipfix_col_external_ids (ovsrec_ipfix_columns[OVSREC_IPFIX_COL_EXTERNAL_IDS])
#define ovsrec_ipfix_col_obs_domain_id (ovsrec_ipfix_columns[OVSREC_IPFIX_COL_OBS_DOMAIN_ID])
#define ovsrec_ipfix_col_obs_point_id (ovsrec_ipfix_columns[OVSREC_IPFIX_COL_OBS_POINT_ID])
#define ovsrec_ipfix_col_other_config (ovsrec_ipfix_columns[OVSREC_IPFIX_COL_OTHER_CONFIG])
#define ovsrec_ipfix_col_sampling (ovsrec_ipfix_columns[OVSREC_IPFIX_COL_SAMPLING])
#define ovsrec_ipfix_col_targets (ovsrec_ipfix_columns[OVSREC_IPFIX_COL_TARGETS])

extern struct ovsdb_idl_column ovsrec_ipfix_columns[OVSREC_IPFIX_N_COLUMNS];
bool ovsrec_server_has_ipfix_table_col_cache_active_timeout(const struct ovsdb_idl *); 
bool ovsrec_server_has_ipfix_table_col_cache_max_flows(const struct ovsdb_idl *); 
bool ovsrec_server_has_ipfix_table_col_external_ids(const struct ovsdb_idl *); 
bool ovsrec_server_has_ipfix_table_col_obs_domain_id(const struct ovsdb_idl *); 
bool ovsrec_server_has_ipfix_table_col_obs_point_id(const struct ovsdb_idl *); 
bool ovsrec_server_has_ipfix_table_col_other_config(const struct ovsdb_idl *); 
bool ovsrec_server_has_ipfix_table_col_sampling(const struct ovsdb_idl *); 
bool ovsrec_server_has_ipfix_table_col_targets(const struct ovsdb_idl *); 

bool ovsrec_server_has_ipfix_table(const struct ovsdb_idl *);
const struct ovsrec_ipfix_table *ovsrec_ipfix_table_get(const struct ovsdb_idl *);
const struct ovsrec_ipfix *ovsrec_ipfix_table_first(const struct ovsrec_ipfix_table *);

#define OVSREC_IPFIX_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_ipfix_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_ipfix_next(ROW))
#define OVSREC_IPFIX_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_ipfix_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_ipfix_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_IPFIX_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_ipfix * ROW__next = ((ROW) = ovsrec_ipfix_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_ipfix_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_IPFIX_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_IPFIX_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_IPFIX_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_ipfix *ovsrec_ipfix_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_ipfix *ovsrec_ipfix_table_get_for_uuid(const struct ovsrec_ipfix_table *, const struct uuid *);
const struct ovsrec_ipfix *ovsrec_ipfix_first(const struct ovsdb_idl *);
const struct ovsrec_ipfix *ovsrec_ipfix_next(const struct ovsrec_ipfix *);
#define OVSREC_IPFIX_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_ipfix_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_ipfix_next(ROW))
#define OVSREC_IPFIX_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_ipfix_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_ipfix_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_IPFIX_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_ipfix * ROW__next = ((ROW) = ovsrec_ipfix_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_ipfix_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_IPFIX_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_IPFIX_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_IPFIX_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_ipfix_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_ipfix_row_get_seqno(const struct ovsrec_ipfix *row, enum ovsdb_idl_change change);
const struct ovsrec_ipfix *ovsrec_ipfix_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_ipfix *ovsrec_ipfix_track_get_next(const struct ovsrec_ipfix *);
#define OVSREC_IPFIX_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_ipfix_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_ipfix_track_get_next(ROW))

const struct ovsrec_ipfix *ovsrec_ipfix_table_track_get_first(const struct ovsrec_ipfix_table *);
#define OVSREC_IPFIX_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_ipfix_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_ipfix_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_ipfix_is_new(const struct ovsrec_ipfix *row)
{
    return ovsrec_ipfix_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_ipfix_is_deleted(const struct ovsrec_ipfix *row)
{
    return ovsrec_ipfix_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_ipfix_index_destroy_row(const struct ovsrec_ipfix *);

struct ovsrec_ipfix *ovsrec_ipfix_index_find(struct ovsdb_idl_index *, const struct ovsrec_ipfix *);

int ovsrec_ipfix_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_ipfix *, 
    const struct ovsrec_ipfix *);
struct ovsdb_idl_cursor ovsrec_ipfix_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_ipfix_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_ipfix *);
struct ovsdb_idl_cursor ovsrec_ipfix_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_ipfix *);

struct ovsrec_ipfix *ovsrec_ipfix_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_IPFIX_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_ipfix_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_ipfix_cursor_data(&cursor__), \
                  !(TO) || ovsrec_ipfix_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_IPFIX_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_ipfix_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_ipfix_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_IPFIX_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_ipfix_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_ipfix_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_ipfix_init(struct ovsrec_ipfix *);
void ovsrec_ipfix_delete(const struct ovsrec_ipfix *);
struct ovsrec_ipfix *ovsrec_ipfix_insert(struct ovsdb_idl_txn *);
struct ovsrec_ipfix *ovsrec_ipfix_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_ipfix_column_id' of
 * the row referenced by 'struct ovsrec_ipfix *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_ipfix_is_updated(const struct ovsrec_ipfix *, enum ovsrec_ipfix_column_id);

void ovsrec_ipfix_verify_cache_active_timeout(const struct ovsrec_ipfix *);
void ovsrec_ipfix_verify_cache_max_flows(const struct ovsrec_ipfix *);
void ovsrec_ipfix_verify_external_ids(const struct ovsrec_ipfix *);
void ovsrec_ipfix_verify_obs_domain_id(const struct ovsrec_ipfix *);
void ovsrec_ipfix_verify_obs_point_id(const struct ovsrec_ipfix *);
void ovsrec_ipfix_verify_other_config(const struct ovsrec_ipfix *);
void ovsrec_ipfix_verify_sampling(const struct ovsrec_ipfix *);
void ovsrec_ipfix_verify_targets(const struct ovsrec_ipfix *);

const struct ovsdb_datum *ovsrec_ipfix_get_cache_active_timeout(const struct ovsrec_ipfix *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_ipfix_get_cache_max_flows(const struct ovsrec_ipfix *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_ipfix_get_external_ids(const struct ovsrec_ipfix *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_ipfix_get_obs_domain_id(const struct ovsrec_ipfix *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_ipfix_get_obs_point_id(const struct ovsrec_ipfix *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_ipfix_get_other_config(const struct ovsrec_ipfix *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_ipfix_get_sampling(const struct ovsrec_ipfix *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_ipfix_get_targets(const struct ovsrec_ipfix *, enum ovsdb_atomic_type key_type);

void ovsrec_ipfix_set_cache_active_timeout(const struct ovsrec_ipfix *, const int64_t *cache_active_timeout, size_t n_cache_active_timeout);
void ovsrec_ipfix_set_cache_max_flows(const struct ovsrec_ipfix *, const int64_t *cache_max_flows, size_t n_cache_max_flows);
void ovsrec_ipfix_set_external_ids(const struct ovsrec_ipfix *, const struct smap *);
void ovsrec_ipfix_set_obs_domain_id(const struct ovsrec_ipfix *, const int64_t *obs_domain_id, size_t n_obs_domain_id);
void ovsrec_ipfix_set_obs_point_id(const struct ovsrec_ipfix *, const int64_t *obs_point_id, size_t n_obs_point_id);
void ovsrec_ipfix_set_other_config(const struct ovsrec_ipfix *, const struct smap *);
void ovsrec_ipfix_set_sampling(const struct ovsrec_ipfix *, const int64_t *sampling, size_t n_sampling);
void ovsrec_ipfix_set_targets(const struct ovsrec_ipfix *, const char **targets, size_t n_targets);

void ovsrec_ipfix_update_cache_active_timeout_addvalue(const struct ovsrec_ipfix *,  int64_t );
void ovsrec_ipfix_update_cache_active_timeout_delvalue(const struct ovsrec_ipfix *,  int64_t );
void ovsrec_ipfix_add_clause_cache_active_timeout(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *cache_active_timeout, size_t n_cache_active_timeout);
unsigned int ovsrec_ipfix_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_ipfix_update_cache_max_flows_addvalue(const struct ovsrec_ipfix *,  int64_t );
void ovsrec_ipfix_update_cache_max_flows_delvalue(const struct ovsrec_ipfix *,  int64_t );
void ovsrec_ipfix_add_clause_cache_max_flows(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *cache_max_flows, size_t n_cache_max_flows);
unsigned int ovsrec_ipfix_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_ipfix_update_external_ids_setkey(const struct ovsrec_ipfix *,  const char *, const char *);
void ovsrec_ipfix_update_external_ids_delkey(const struct ovsrec_ipfix *,  const char *);
void ovsrec_ipfix_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_ipfix_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_ipfix_update_obs_domain_id_addvalue(const struct ovsrec_ipfix *,  int64_t );
void ovsrec_ipfix_update_obs_domain_id_delvalue(const struct ovsrec_ipfix *,  int64_t );
void ovsrec_ipfix_add_clause_obs_domain_id(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *obs_domain_id, size_t n_obs_domain_id);
unsigned int ovsrec_ipfix_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_ipfix_update_obs_point_id_addvalue(const struct ovsrec_ipfix *,  int64_t );
void ovsrec_ipfix_update_obs_point_id_delvalue(const struct ovsrec_ipfix *,  int64_t );
void ovsrec_ipfix_add_clause_obs_point_id(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *obs_point_id, size_t n_obs_point_id);
unsigned int ovsrec_ipfix_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_ipfix_update_other_config_setkey(const struct ovsrec_ipfix *,  const char *, const char *);
void ovsrec_ipfix_update_other_config_delkey(const struct ovsrec_ipfix *,  const char *);
void ovsrec_ipfix_add_clause_other_config(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_ipfix_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_ipfix_update_sampling_addvalue(const struct ovsrec_ipfix *,  int64_t );
void ovsrec_ipfix_update_sampling_delvalue(const struct ovsrec_ipfix *,  int64_t );
void ovsrec_ipfix_add_clause_sampling(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *sampling, size_t n_sampling);
unsigned int ovsrec_ipfix_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_ipfix_update_targets_addvalue(const struct ovsrec_ipfix *,  const char *);
void ovsrec_ipfix_update_targets_delvalue(const struct ovsrec_ipfix *,  const char *);
void ovsrec_ipfix_add_clause_targets(struct ovsdb_idl_condition *, enum ovsdb_function function, const char **targets, size_t n_targets);
unsigned int ovsrec_ipfix_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_ipfix *ovsrec_ipfix_index_init_row(struct ovsdb_idl_index *);
void ovsrec_ipfix_index_set_cache_active_timeout(const struct ovsrec_ipfix *,
const int64_t *cache_active_timeout, size_t n_cache_active_timeout);
void ovsrec_ipfix_index_set_cache_max_flows(const struct ovsrec_ipfix *,
const int64_t *cache_max_flows, size_t n_cache_max_flows);
void ovsrec_ipfix_index_set_external_ids(const struct ovsrec_ipfix *,
const struct smap *);
void ovsrec_ipfix_index_set_obs_domain_id(const struct ovsrec_ipfix *,
const int64_t *obs_domain_id, size_t n_obs_domain_id);
void ovsrec_ipfix_index_set_obs_point_id(const struct ovsrec_ipfix *,
const int64_t *obs_point_id, size_t n_obs_point_id);
void ovsrec_ipfix_index_set_other_config(const struct ovsrec_ipfix *,
const struct smap *);
void ovsrec_ipfix_index_set_sampling(const struct ovsrec_ipfix *,
const int64_t *sampling, size_t n_sampling);
void ovsrec_ipfix_index_set_targets(const struct ovsrec_ipfix *,
const char **targets, size_t n_targets);

/* Interface table. */
struct ovsrec_interface {
	struct ovsdb_idl_row header_;

	/* admin_state column. */
	char *admin_state;

	/* bfd column. */
	struct smap bfd;

	/* bfd_status column. */
	struct smap bfd_status;

	/* cfm_fault column. */
	bool *cfm_fault;
	size_t n_cfm_fault;

	/* cfm_fault_status column. */
	char **cfm_fault_status;
	size_t n_cfm_fault_status;

	/* cfm_flap_count column. */
	int64_t *cfm_flap_count;
	size_t n_cfm_flap_count;

	/* cfm_health column. */
	int64_t *cfm_health;
	size_t n_cfm_health;

	/* cfm_mpid column. */
	int64_t *cfm_mpid;
	size_t n_cfm_mpid;

	/* cfm_remote_mpids column. */
	int64_t *cfm_remote_mpids;
	size_t n_cfm_remote_mpids;

	/* cfm_remote_opstate column. */
	char *cfm_remote_opstate;

	/* duplex column. */
	char *duplex;

	/* error column. */
	char *error;

	/* external_ids column. */
	struct smap external_ids;

	/* ifindex column. */
	int64_t *ifindex;
	size_t n_ifindex;

	/* ingress_policing_burst column. */
	int64_t ingress_policing_burst;

	/* ingress_policing_kpkts_burst column. */
	int64_t ingress_policing_kpkts_burst;

	/* ingress_policing_kpkts_rate column. */
	int64_t ingress_policing_kpkts_rate;

	/* ingress_policing_rate column. */
	int64_t ingress_policing_rate;

	/* lacp_current column. */
	bool *lacp_current;
	size_t n_lacp_current;

	/* link_resets column. */
	int64_t *link_resets;
	size_t n_link_resets;

	/* link_speed column. */
	int64_t *link_speed;
	size_t n_link_speed;

	/* link_state column. */
	char *link_state;

	/* lldp column. */
	struct smap lldp;

	/* mac column. */
	char *mac;

	/* mac_in_use column. */
	char *mac_in_use;

	/* mtu column. */
	int64_t *mtu;
	size_t n_mtu;

	/* mtu_request column. */
	int64_t *mtu_request;
	size_t n_mtu_request;

	/* name column. */
	char *name;	/* Always nonnull. */

	/* ofport column. */
	int64_t *ofport;
	size_t n_ofport;

	/* ofport_request column. */
	int64_t *ofport_request;
	size_t n_ofport_request;

	/* options column. */
	struct smap options;

	/* other_config column. */
	struct smap other_config;

	/* statistics column. */
	char **key_statistics;
	int64_t *value_statistics;
	size_t n_statistics;

	/* status column. */
	struct smap status;

	/* type column. */
	char *type;	/* Always nonnull. */
};

enum ovsrec_interface_column_id {
    OVSREC_INTERFACE_COL_ADMIN_STATE,
    OVSREC_INTERFACE_COL_BFD,
    OVSREC_INTERFACE_COL_BFD_STATUS,
    OVSREC_INTERFACE_COL_CFM_FAULT,
    OVSREC_INTERFACE_COL_CFM_FAULT_STATUS,
    OVSREC_INTERFACE_COL_CFM_FLAP_COUNT,
    OVSREC_INTERFACE_COL_CFM_HEALTH,
    OVSREC_INTERFACE_COL_CFM_MPID,
    OVSREC_INTERFACE_COL_CFM_REMOTE_MPIDS,
    OVSREC_INTERFACE_COL_CFM_REMOTE_OPSTATE,
    OVSREC_INTERFACE_COL_DUPLEX,
    OVSREC_INTERFACE_COL_ERROR,
    OVSREC_INTERFACE_COL_EXTERNAL_IDS,
    OVSREC_INTERFACE_COL_IFINDEX,
    OVSREC_INTERFACE_COL_INGRESS_POLICING_BURST,
    OVSREC_INTERFACE_COL_INGRESS_POLICING_KPKTS_BURST,
    OVSREC_INTERFACE_COL_INGRESS_POLICING_KPKTS_RATE,
    OVSREC_INTERFACE_COL_INGRESS_POLICING_RATE,
    OVSREC_INTERFACE_COL_LACP_CURRENT,
    OVSREC_INTERFACE_COL_LINK_RESETS,
    OVSREC_INTERFACE_COL_LINK_SPEED,
    OVSREC_INTERFACE_COL_LINK_STATE,
    OVSREC_INTERFACE_COL_LLDP,
    OVSREC_INTERFACE_COL_MAC,
    OVSREC_INTERFACE_COL_MAC_IN_USE,
    OVSREC_INTERFACE_COL_MTU,
    OVSREC_INTERFACE_COL_MTU_REQUEST,
    OVSREC_INTERFACE_COL_NAME,
    OVSREC_INTERFACE_COL_OFPORT,
    OVSREC_INTERFACE_COL_OFPORT_REQUEST,
    OVSREC_INTERFACE_COL_OPTIONS,
    OVSREC_INTERFACE_COL_OTHER_CONFIG,
    OVSREC_INTERFACE_COL_STATISTICS,
    OVSREC_INTERFACE_COL_STATUS,
    OVSREC_INTERFACE_COL_TYPE,
    OVSREC_INTERFACE_N_COLUMNS
};

#define ovsrec_interface_col_admin_state (ovsrec_interface_columns[OVSREC_INTERFACE_COL_ADMIN_STATE])
#define ovsrec_interface_col_bfd (ovsrec_interface_columns[OVSREC_INTERFACE_COL_BFD])
#define ovsrec_interface_col_bfd_status (ovsrec_interface_columns[OVSREC_INTERFACE_COL_BFD_STATUS])
#define ovsrec_interface_col_cfm_fault (ovsrec_interface_columns[OVSREC_INTERFACE_COL_CFM_FAULT])
#define ovsrec_interface_col_cfm_fault_status (ovsrec_interface_columns[OVSREC_INTERFACE_COL_CFM_FAULT_STATUS])
#define ovsrec_interface_col_cfm_flap_count (ovsrec_interface_columns[OVSREC_INTERFACE_COL_CFM_FLAP_COUNT])
#define ovsrec_interface_col_cfm_health (ovsrec_interface_columns[OVSREC_INTERFACE_COL_CFM_HEALTH])
#define ovsrec_interface_col_cfm_mpid (ovsrec_interface_columns[OVSREC_INTERFACE_COL_CFM_MPID])
#define ovsrec_interface_col_cfm_remote_mpids (ovsrec_interface_columns[OVSREC_INTERFACE_COL_CFM_REMOTE_MPIDS])
#define ovsrec_interface_col_cfm_remote_opstate (ovsrec_interface_columns[OVSREC_INTERFACE_COL_CFM_REMOTE_OPSTATE])
#define ovsrec_interface_col_duplex (ovsrec_interface_columns[OVSREC_INTERFACE_COL_DUPLEX])
#define ovsrec_interface_col_error (ovsrec_interface_columns[OVSREC_INTERFACE_COL_ERROR])
#define ovsrec_interface_col_external_ids (ovsrec_interface_columns[OVSREC_INTERFACE_COL_EXTERNAL_IDS])
#define ovsrec_interface_col_ifindex (ovsrec_interface_columns[OVSREC_INTERFACE_COL_IFINDEX])
#define ovsrec_interface_col_ingress_policing_burst (ovsrec_interface_columns[OVSREC_INTERFACE_COL_INGRESS_POLICING_BURST])
#define ovsrec_interface_col_ingress_policing_kpkts_burst (ovsrec_interface_columns[OVSREC_INTERFACE_COL_INGRESS_POLICING_KPKTS_BURST])
#define ovsrec_interface_col_ingress_policing_kpkts_rate (ovsrec_interface_columns[OVSREC_INTERFACE_COL_INGRESS_POLICING_KPKTS_RATE])
#define ovsrec_interface_col_ingress_policing_rate (ovsrec_interface_columns[OVSREC_INTERFACE_COL_INGRESS_POLICING_RATE])
#define ovsrec_interface_col_lacp_current (ovsrec_interface_columns[OVSREC_INTERFACE_COL_LACP_CURRENT])
#define ovsrec_interface_col_link_resets (ovsrec_interface_columns[OVSREC_INTERFACE_COL_LINK_RESETS])
#define ovsrec_interface_col_link_speed (ovsrec_interface_columns[OVSREC_INTERFACE_COL_LINK_SPEED])
#define ovsrec_interface_col_link_state (ovsrec_interface_columns[OVSREC_INTERFACE_COL_LINK_STATE])
#define ovsrec_interface_col_lldp (ovsrec_interface_columns[OVSREC_INTERFACE_COL_LLDP])
#define ovsrec_interface_col_mac (ovsrec_interface_columns[OVSREC_INTERFACE_COL_MAC])
#define ovsrec_interface_col_mac_in_use (ovsrec_interface_columns[OVSREC_INTERFACE_COL_MAC_IN_USE])
#define ovsrec_interface_col_mtu (ovsrec_interface_columns[OVSREC_INTERFACE_COL_MTU])
#define ovsrec_interface_col_mtu_request (ovsrec_interface_columns[OVSREC_INTERFACE_COL_MTU_REQUEST])
#define ovsrec_interface_col_name (ovsrec_interface_columns[OVSREC_INTERFACE_COL_NAME])
#define ovsrec_interface_col_ofport (ovsrec_interface_columns[OVSREC_INTERFACE_COL_OFPORT])
#define ovsrec_interface_col_ofport_request (ovsrec_interface_columns[OVSREC_INTERFACE_COL_OFPORT_REQUEST])
#define ovsrec_interface_col_options (ovsrec_interface_columns[OVSREC_INTERFACE_COL_OPTIONS])
#define ovsrec_interface_col_other_config (ovsrec_interface_columns[OVSREC_INTERFACE_COL_OTHER_CONFIG])
#define ovsrec_interface_col_statistics (ovsrec_interface_columns[OVSREC_INTERFACE_COL_STATISTICS])
#define ovsrec_interface_col_status (ovsrec_interface_columns[OVSREC_INTERFACE_COL_STATUS])
#define ovsrec_interface_col_type (ovsrec_interface_columns[OVSREC_INTERFACE_COL_TYPE])

extern struct ovsdb_idl_column ovsrec_interface_columns[OVSREC_INTERFACE_N_COLUMNS];
bool ovsrec_server_has_interface_table_col_admin_state(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_bfd(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_bfd_status(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_cfm_fault(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_cfm_fault_status(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_cfm_flap_count(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_cfm_health(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_cfm_mpid(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_cfm_remote_mpids(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_cfm_remote_opstate(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_duplex(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_error(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_external_ids(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_ifindex(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_ingress_policing_burst(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_ingress_policing_kpkts_burst(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_ingress_policing_kpkts_rate(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_ingress_policing_rate(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_lacp_current(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_link_resets(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_link_speed(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_link_state(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_lldp(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_mac(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_mac_in_use(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_mtu(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_mtu_request(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_name(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_ofport(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_ofport_request(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_options(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_other_config(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_statistics(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_status(const struct ovsdb_idl *); 
bool ovsrec_server_has_interface_table_col_type(const struct ovsdb_idl *); 

bool ovsrec_server_has_interface_table(const struct ovsdb_idl *);
const struct ovsrec_interface_table *ovsrec_interface_table_get(const struct ovsdb_idl *);
const struct ovsrec_interface *ovsrec_interface_table_first(const struct ovsrec_interface_table *);

#define OVSREC_INTERFACE_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_interface_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_interface_next(ROW))
#define OVSREC_INTERFACE_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_interface_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_interface_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_INTERFACE_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_interface * ROW__next = ((ROW) = ovsrec_interface_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_interface_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_INTERFACE_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_INTERFACE_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_INTERFACE_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_interface *ovsrec_interface_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_interface *ovsrec_interface_table_get_for_uuid(const struct ovsrec_interface_table *, const struct uuid *);
const struct ovsrec_interface *ovsrec_interface_first(const struct ovsdb_idl *);
const struct ovsrec_interface *ovsrec_interface_next(const struct ovsrec_interface *);
#define OVSREC_INTERFACE_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_interface_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_interface_next(ROW))
#define OVSREC_INTERFACE_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_interface_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_interface_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_INTERFACE_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_interface * ROW__next = ((ROW) = ovsrec_interface_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_interface_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_INTERFACE_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_INTERFACE_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_INTERFACE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_interface_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_interface_row_get_seqno(const struct ovsrec_interface *row, enum ovsdb_idl_change change);
const struct ovsrec_interface *ovsrec_interface_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_interface *ovsrec_interface_track_get_next(const struct ovsrec_interface *);
#define OVSREC_INTERFACE_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_interface_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_interface_track_get_next(ROW))

const struct ovsrec_interface *ovsrec_interface_table_track_get_first(const struct ovsrec_interface_table *);
#define OVSREC_INTERFACE_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_interface_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_interface_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_interface_is_new(const struct ovsrec_interface *row)
{
    return ovsrec_interface_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_interface_is_deleted(const struct ovsrec_interface *row)
{
    return ovsrec_interface_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_interface_index_destroy_row(const struct ovsrec_interface *);

struct ovsrec_interface *ovsrec_interface_index_find(struct ovsdb_idl_index *, const struct ovsrec_interface *);

int ovsrec_interface_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_interface *, 
    const struct ovsrec_interface *);
struct ovsdb_idl_cursor ovsrec_interface_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_interface_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_interface *);
struct ovsdb_idl_cursor ovsrec_interface_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_interface *);

struct ovsrec_interface *ovsrec_interface_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_INTERFACE_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_interface_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_interface_cursor_data(&cursor__), \
                  !(TO) || ovsrec_interface_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_INTERFACE_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_interface_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_interface_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_INTERFACE_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_interface_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_interface_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_interface_init(struct ovsrec_interface *);
void ovsrec_interface_delete(const struct ovsrec_interface *);
struct ovsrec_interface *ovsrec_interface_insert(struct ovsdb_idl_txn *);
struct ovsrec_interface *ovsrec_interface_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_interface_column_id' of
 * the row referenced by 'struct ovsrec_interface *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_interface_is_updated(const struct ovsrec_interface *, enum ovsrec_interface_column_id);

void ovsrec_interface_verify_admin_state(const struct ovsrec_interface *);
void ovsrec_interface_verify_bfd(const struct ovsrec_interface *);
void ovsrec_interface_verify_bfd_status(const struct ovsrec_interface *);
void ovsrec_interface_verify_cfm_fault(const struct ovsrec_interface *);
void ovsrec_interface_verify_cfm_fault_status(const struct ovsrec_interface *);
void ovsrec_interface_verify_cfm_flap_count(const struct ovsrec_interface *);
void ovsrec_interface_verify_cfm_health(const struct ovsrec_interface *);
void ovsrec_interface_verify_cfm_mpid(const struct ovsrec_interface *);
void ovsrec_interface_verify_cfm_remote_mpids(const struct ovsrec_interface *);
void ovsrec_interface_verify_cfm_remote_opstate(const struct ovsrec_interface *);
void ovsrec_interface_verify_duplex(const struct ovsrec_interface *);
void ovsrec_interface_verify_error(const struct ovsrec_interface *);
void ovsrec_interface_verify_external_ids(const struct ovsrec_interface *);
void ovsrec_interface_verify_ifindex(const struct ovsrec_interface *);
void ovsrec_interface_verify_ingress_policing_burst(const struct ovsrec_interface *);
void ovsrec_interface_verify_ingress_policing_kpkts_burst(const struct ovsrec_interface *);
void ovsrec_interface_verify_ingress_policing_kpkts_rate(const struct ovsrec_interface *);
void ovsrec_interface_verify_ingress_policing_rate(const struct ovsrec_interface *);
void ovsrec_interface_verify_lacp_current(const struct ovsrec_interface *);
void ovsrec_interface_verify_link_resets(const struct ovsrec_interface *);
void ovsrec_interface_verify_link_speed(const struct ovsrec_interface *);
void ovsrec_interface_verify_link_state(const struct ovsrec_interface *);
void ovsrec_interface_verify_lldp(const struct ovsrec_interface *);
void ovsrec_interface_verify_mac(const struct ovsrec_interface *);
void ovsrec_interface_verify_mac_in_use(const struct ovsrec_interface *);
void ovsrec_interface_verify_mtu(const struct ovsrec_interface *);
void ovsrec_interface_verify_mtu_request(const struct ovsrec_interface *);
void ovsrec_interface_verify_name(const struct ovsrec_interface *);
void ovsrec_interface_verify_ofport(const struct ovsrec_interface *);
void ovsrec_interface_verify_ofport_request(const struct ovsrec_interface *);
void ovsrec_interface_verify_options(const struct ovsrec_interface *);
void ovsrec_interface_verify_other_config(const struct ovsrec_interface *);
void ovsrec_interface_verify_statistics(const struct ovsrec_interface *);
void ovsrec_interface_verify_status(const struct ovsrec_interface *);
void ovsrec_interface_verify_type(const struct ovsrec_interface *);

const struct ovsdb_datum *ovsrec_interface_get_admin_state(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_bfd(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_interface_get_bfd_status(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_interface_get_cfm_fault(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_cfm_fault_status(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_cfm_flap_count(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_cfm_health(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_cfm_mpid(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_cfm_remote_mpids(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_cfm_remote_opstate(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_duplex(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_error(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_external_ids(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_interface_get_ifindex(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_ingress_policing_burst(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_ingress_policing_kpkts_burst(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_ingress_policing_kpkts_rate(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_ingress_policing_rate(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_lacp_current(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_link_resets(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_link_speed(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_link_state(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_lldp(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_interface_get_mac(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_mac_in_use(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_mtu(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_mtu_request(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_name(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_ofport(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_ofport_request(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_interface_get_options(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_interface_get_other_config(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_interface_get_statistics(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_interface_get_status(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_interface_get_type(const struct ovsrec_interface *, enum ovsdb_atomic_type key_type);

void ovsrec_interface_set_admin_state(const struct ovsrec_interface *, const char *admin_state);
void ovsrec_interface_set_bfd(const struct ovsrec_interface *, const struct smap *);
void ovsrec_interface_set_bfd_status(const struct ovsrec_interface *, const struct smap *);
void ovsrec_interface_set_cfm_fault(const struct ovsrec_interface *, const bool *cfm_fault, size_t n_cfm_fault);
void ovsrec_interface_set_cfm_fault_status(const struct ovsrec_interface *, const char **cfm_fault_status, size_t n_cfm_fault_status);
void ovsrec_interface_set_cfm_flap_count(const struct ovsrec_interface *, const int64_t *cfm_flap_count, size_t n_cfm_flap_count);
void ovsrec_interface_set_cfm_health(const struct ovsrec_interface *, const int64_t *cfm_health, size_t n_cfm_health);
void ovsrec_interface_set_cfm_mpid(const struct ovsrec_interface *, const int64_t *cfm_mpid, size_t n_cfm_mpid);
void ovsrec_interface_set_cfm_remote_mpids(const struct ovsrec_interface *, const int64_t *cfm_remote_mpids, size_t n_cfm_remote_mpids);
void ovsrec_interface_set_cfm_remote_opstate(const struct ovsrec_interface *, const char *cfm_remote_opstate);
void ovsrec_interface_set_duplex(const struct ovsrec_interface *, const char *duplex);
void ovsrec_interface_set_error(const struct ovsrec_interface *, const char *error);
void ovsrec_interface_set_external_ids(const struct ovsrec_interface *, const struct smap *);
void ovsrec_interface_set_ifindex(const struct ovsrec_interface *, const int64_t *ifindex, size_t n_ifindex);
void ovsrec_interface_set_ingress_policing_burst(const struct ovsrec_interface *, int64_t ingress_policing_burst);
void ovsrec_interface_set_ingress_policing_kpkts_burst(const struct ovsrec_interface *, int64_t ingress_policing_kpkts_burst);
void ovsrec_interface_set_ingress_policing_kpkts_rate(const struct ovsrec_interface *, int64_t ingress_policing_kpkts_rate);
void ovsrec_interface_set_ingress_policing_rate(const struct ovsrec_interface *, int64_t ingress_policing_rate);
void ovsrec_interface_set_lacp_current(const struct ovsrec_interface *, const bool *lacp_current, size_t n_lacp_current);
void ovsrec_interface_set_link_resets(const struct ovsrec_interface *, const int64_t *link_resets, size_t n_link_resets);
void ovsrec_interface_set_link_speed(const struct ovsrec_interface *, const int64_t *link_speed, size_t n_link_speed);
void ovsrec_interface_set_link_state(const struct ovsrec_interface *, const char *link_state);
void ovsrec_interface_set_lldp(const struct ovsrec_interface *, const struct smap *);
void ovsrec_interface_set_mac(const struct ovsrec_interface *, const char *mac);
void ovsrec_interface_set_mac_in_use(const struct ovsrec_interface *, const char *mac_in_use);
void ovsrec_interface_set_mtu(const struct ovsrec_interface *, const int64_t *mtu, size_t n_mtu);
void ovsrec_interface_set_mtu_request(const struct ovsrec_interface *, const int64_t *mtu_request, size_t n_mtu_request);
void ovsrec_interface_set_name(const struct ovsrec_interface *, const char *name);
void ovsrec_interface_set_ofport(const struct ovsrec_interface *, const int64_t *ofport, size_t n_ofport);
void ovsrec_interface_set_ofport_request(const struct ovsrec_interface *, const int64_t *ofport_request, size_t n_ofport_request);
void ovsrec_interface_set_options(const struct ovsrec_interface *, const struct smap *);
void ovsrec_interface_set_other_config(const struct ovsrec_interface *, const struct smap *);
void ovsrec_interface_set_statistics(const struct ovsrec_interface *, const char **key_statistics, const int64_t *value_statistics, size_t n_statistics);
void ovsrec_interface_set_status(const struct ovsrec_interface *, const struct smap *);
void ovsrec_interface_set_type(const struct ovsrec_interface *, const char *type);

void ovsrec_interface_update_admin_state_addvalue(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_update_admin_state_delvalue(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_add_clause_admin_state(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *admin_state);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_bfd_setkey(const struct ovsrec_interface *,  const char *, const char *);
void ovsrec_interface_update_bfd_delkey(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_add_clause_bfd(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_bfd_status_setkey(const struct ovsrec_interface *,  const char *, const char *);
void ovsrec_interface_update_bfd_status_delkey(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_add_clause_bfd_status(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_cfm_fault_addvalue(const struct ovsrec_interface *,  bool );
void ovsrec_interface_update_cfm_fault_delvalue(const struct ovsrec_interface *,  bool );
void ovsrec_interface_add_clause_cfm_fault(struct ovsdb_idl_condition *, enum ovsdb_function function, const bool *cfm_fault, size_t n_cfm_fault);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_cfm_fault_status_addvalue(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_update_cfm_fault_status_delvalue(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_add_clause_cfm_fault_status(struct ovsdb_idl_condition *, enum ovsdb_function function, const char **cfm_fault_status, size_t n_cfm_fault_status);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_cfm_flap_count_addvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_update_cfm_flap_count_delvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_add_clause_cfm_flap_count(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *cfm_flap_count, size_t n_cfm_flap_count);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_cfm_health_addvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_update_cfm_health_delvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_add_clause_cfm_health(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *cfm_health, size_t n_cfm_health);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_cfm_mpid_addvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_update_cfm_mpid_delvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_add_clause_cfm_mpid(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *cfm_mpid, size_t n_cfm_mpid);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_cfm_remote_mpids_addvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_update_cfm_remote_mpids_delvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_add_clause_cfm_remote_mpids(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *cfm_remote_mpids, size_t n_cfm_remote_mpids);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_cfm_remote_opstate_addvalue(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_update_cfm_remote_opstate_delvalue(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_add_clause_cfm_remote_opstate(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *cfm_remote_opstate);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_duplex_addvalue(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_update_duplex_delvalue(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_add_clause_duplex(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *duplex);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_error_addvalue(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_update_error_delvalue(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_add_clause_error(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *error);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_external_ids_setkey(const struct ovsrec_interface *,  const char *, const char *);
void ovsrec_interface_update_external_ids_delkey(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_ifindex_addvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_update_ifindex_delvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_add_clause_ifindex(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *ifindex, size_t n_ifindex);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_add_clause_ingress_policing_burst(struct ovsdb_idl_condition *, enum ovsdb_function function, int64_t ingress_policing_burst);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_add_clause_ingress_policing_kpkts_burst(struct ovsdb_idl_condition *, enum ovsdb_function function, int64_t ingress_policing_kpkts_burst);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_add_clause_ingress_policing_kpkts_rate(struct ovsdb_idl_condition *, enum ovsdb_function function, int64_t ingress_policing_kpkts_rate);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_add_clause_ingress_policing_rate(struct ovsdb_idl_condition *, enum ovsdb_function function, int64_t ingress_policing_rate);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_lacp_current_addvalue(const struct ovsrec_interface *,  bool );
void ovsrec_interface_update_lacp_current_delvalue(const struct ovsrec_interface *,  bool );
void ovsrec_interface_add_clause_lacp_current(struct ovsdb_idl_condition *, enum ovsdb_function function, const bool *lacp_current, size_t n_lacp_current);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_link_resets_addvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_update_link_resets_delvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_add_clause_link_resets(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *link_resets, size_t n_link_resets);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_link_speed_addvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_update_link_speed_delvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_add_clause_link_speed(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *link_speed, size_t n_link_speed);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_link_state_addvalue(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_update_link_state_delvalue(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_add_clause_link_state(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *link_state);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_lldp_setkey(const struct ovsrec_interface *,  const char *, const char *);
void ovsrec_interface_update_lldp_delkey(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_add_clause_lldp(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_mac_addvalue(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_update_mac_delvalue(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_add_clause_mac(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *mac);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_mac_in_use_addvalue(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_update_mac_in_use_delvalue(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_add_clause_mac_in_use(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *mac_in_use);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_mtu_addvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_update_mtu_delvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_add_clause_mtu(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *mtu, size_t n_mtu);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_mtu_request_addvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_update_mtu_request_delvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_add_clause_mtu_request(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *mtu_request, size_t n_mtu_request);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_add_clause_name(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *name);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_ofport_addvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_update_ofport_delvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_add_clause_ofport(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *ofport, size_t n_ofport);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_ofport_request_addvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_update_ofport_request_delvalue(const struct ovsrec_interface *,  int64_t );
void ovsrec_interface_add_clause_ofport_request(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *ofport_request, size_t n_ofport_request);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_options_setkey(const struct ovsrec_interface *,  const char *, const char *);
void ovsrec_interface_update_options_delkey(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_add_clause_options(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_other_config_setkey(const struct ovsrec_interface *,  const char *, const char *);
void ovsrec_interface_update_other_config_delkey(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_add_clause_other_config(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_statistics_setkey(const struct ovsrec_interface *,  const char *, int64_t );
void ovsrec_interface_update_statistics_delkey(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_add_clause_statistics(struct ovsdb_idl_condition *, enum ovsdb_function function, const char **key_statistics, const int64_t *value_statistics, size_t n_statistics);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_update_status_setkey(const struct ovsrec_interface *,  const char *, const char *);
void ovsrec_interface_update_status_delkey(const struct ovsrec_interface *,  const char *);
void ovsrec_interface_add_clause_status(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_interface_add_clause_type(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *type);
unsigned int ovsrec_interface_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_interface *ovsrec_interface_index_init_row(struct ovsdb_idl_index *);
void ovsrec_interface_index_set_admin_state(const struct ovsrec_interface *,
const char *admin_state);
void ovsrec_interface_index_set_bfd(const struct ovsrec_interface *,
const struct smap *);
void ovsrec_interface_index_set_bfd_status(const struct ovsrec_interface *,
const struct smap *);
void ovsrec_interface_index_set_cfm_fault(const struct ovsrec_interface *,
const bool *cfm_fault, size_t n_cfm_fault);
void ovsrec_interface_index_set_cfm_fault_status(const struct ovsrec_interface *,
const char **cfm_fault_status, size_t n_cfm_fault_status);
void ovsrec_interface_index_set_cfm_flap_count(const struct ovsrec_interface *,
const int64_t *cfm_flap_count, size_t n_cfm_flap_count);
void ovsrec_interface_index_set_cfm_health(const struct ovsrec_interface *,
const int64_t *cfm_health, size_t n_cfm_health);
void ovsrec_interface_index_set_cfm_mpid(const struct ovsrec_interface *,
const int64_t *cfm_mpid, size_t n_cfm_mpid);
void ovsrec_interface_index_set_cfm_remote_mpids(const struct ovsrec_interface *,
const int64_t *cfm_remote_mpids, size_t n_cfm_remote_mpids);
void ovsrec_interface_index_set_cfm_remote_opstate(const struct ovsrec_interface *,
const char *cfm_remote_opstate);
void ovsrec_interface_index_set_duplex(const struct ovsrec_interface *,
const char *duplex);
void ovsrec_interface_index_set_error(const struct ovsrec_interface *,
const char *error);
void ovsrec_interface_index_set_external_ids(const struct ovsrec_interface *,
const struct smap *);
void ovsrec_interface_index_set_ifindex(const struct ovsrec_interface *,
const int64_t *ifindex, size_t n_ifindex);
void ovsrec_interface_index_set_ingress_policing_burst(const struct ovsrec_interface *,
int64_t ingress_policing_burst);
void ovsrec_interface_index_set_ingress_policing_kpkts_burst(const struct ovsrec_interface *,
int64_t ingress_policing_kpkts_burst);
void ovsrec_interface_index_set_ingress_policing_kpkts_rate(const struct ovsrec_interface *,
int64_t ingress_policing_kpkts_rate);
void ovsrec_interface_index_set_ingress_policing_rate(const struct ovsrec_interface *,
int64_t ingress_policing_rate);
void ovsrec_interface_index_set_lacp_current(const struct ovsrec_interface *,
const bool *lacp_current, size_t n_lacp_current);
void ovsrec_interface_index_set_link_resets(const struct ovsrec_interface *,
const int64_t *link_resets, size_t n_link_resets);
void ovsrec_interface_index_set_link_speed(const struct ovsrec_interface *,
const int64_t *link_speed, size_t n_link_speed);
void ovsrec_interface_index_set_link_state(const struct ovsrec_interface *,
const char *link_state);
void ovsrec_interface_index_set_lldp(const struct ovsrec_interface *,
const struct smap *);
void ovsrec_interface_index_set_mac(const struct ovsrec_interface *,
const char *mac);
void ovsrec_interface_index_set_mac_in_use(const struct ovsrec_interface *,
const char *mac_in_use);
void ovsrec_interface_index_set_mtu(const struct ovsrec_interface *,
const int64_t *mtu, size_t n_mtu);
void ovsrec_interface_index_set_mtu_request(const struct ovsrec_interface *,
const int64_t *mtu_request, size_t n_mtu_request);
void ovsrec_interface_index_set_name(const struct ovsrec_interface *,
const char *name);
void ovsrec_interface_index_set_ofport(const struct ovsrec_interface *,
const int64_t *ofport, size_t n_ofport);
void ovsrec_interface_index_set_ofport_request(const struct ovsrec_interface *,
const int64_t *ofport_request, size_t n_ofport_request);
void ovsrec_interface_index_set_options(const struct ovsrec_interface *,
const struct smap *);
void ovsrec_interface_index_set_other_config(const struct ovsrec_interface *,
const struct smap *);
void ovsrec_interface_index_set_statistics(const struct ovsrec_interface *,
const char **key_statistics, const int64_t *value_statistics, size_t n_statistics);
void ovsrec_interface_index_set_status(const struct ovsrec_interface *,
const struct smap *);
void ovsrec_interface_index_set_type(const struct ovsrec_interface *,
const char *type);

/* Manager table. */
struct ovsrec_manager {
	struct ovsdb_idl_row header_;

	/* connection_mode column. */
	char *connection_mode;

	/* external_ids column. */
	struct smap external_ids;

	/* inactivity_probe column. */
	int64_t *inactivity_probe;
	size_t n_inactivity_probe;

	/* is_connected column. */
	bool is_connected;

	/* max_backoff column. */
	int64_t *max_backoff;
	size_t n_max_backoff;

	/* other_config column. */
	struct smap other_config;

	/* status column. */
	struct smap status;

	/* target column. */
	char *target;	/* Always nonnull. */
};

enum ovsrec_manager_column_id {
    OVSREC_MANAGER_COL_CONNECTION_MODE,
    OVSREC_MANAGER_COL_EXTERNAL_IDS,
    OVSREC_MANAGER_COL_INACTIVITY_PROBE,
    OVSREC_MANAGER_COL_IS_CONNECTED,
    OVSREC_MANAGER_COL_MAX_BACKOFF,
    OVSREC_MANAGER_COL_OTHER_CONFIG,
    OVSREC_MANAGER_COL_STATUS,
    OVSREC_MANAGER_COL_TARGET,
    OVSREC_MANAGER_N_COLUMNS
};

#define ovsrec_manager_col_connection_mode (ovsrec_manager_columns[OVSREC_MANAGER_COL_CONNECTION_MODE])
#define ovsrec_manager_col_external_ids (ovsrec_manager_columns[OVSREC_MANAGER_COL_EXTERNAL_IDS])
#define ovsrec_manager_col_inactivity_probe (ovsrec_manager_columns[OVSREC_MANAGER_COL_INACTIVITY_PROBE])
#define ovsrec_manager_col_is_connected (ovsrec_manager_columns[OVSREC_MANAGER_COL_IS_CONNECTED])
#define ovsrec_manager_col_max_backoff (ovsrec_manager_columns[OVSREC_MANAGER_COL_MAX_BACKOFF])
#define ovsrec_manager_col_other_config (ovsrec_manager_columns[OVSREC_MANAGER_COL_OTHER_CONFIG])
#define ovsrec_manager_col_status (ovsrec_manager_columns[OVSREC_MANAGER_COL_STATUS])
#define ovsrec_manager_col_target (ovsrec_manager_columns[OVSREC_MANAGER_COL_TARGET])

extern struct ovsdb_idl_column ovsrec_manager_columns[OVSREC_MANAGER_N_COLUMNS];
bool ovsrec_server_has_manager_table_col_connection_mode(const struct ovsdb_idl *); 
bool ovsrec_server_has_manager_table_col_external_ids(const struct ovsdb_idl *); 
bool ovsrec_server_has_manager_table_col_inactivity_probe(const struct ovsdb_idl *); 
bool ovsrec_server_has_manager_table_col_is_connected(const struct ovsdb_idl *); 
bool ovsrec_server_has_manager_table_col_max_backoff(const struct ovsdb_idl *); 
bool ovsrec_server_has_manager_table_col_other_config(const struct ovsdb_idl *); 
bool ovsrec_server_has_manager_table_col_status(const struct ovsdb_idl *); 
bool ovsrec_server_has_manager_table_col_target(const struct ovsdb_idl *); 

bool ovsrec_server_has_manager_table(const struct ovsdb_idl *);
const struct ovsrec_manager_table *ovsrec_manager_table_get(const struct ovsdb_idl *);
const struct ovsrec_manager *ovsrec_manager_table_first(const struct ovsrec_manager_table *);

#define OVSREC_MANAGER_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_manager_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_manager_next(ROW))
#define OVSREC_MANAGER_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_manager_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_manager_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_MANAGER_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_manager * ROW__next = ((ROW) = ovsrec_manager_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_manager_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_MANAGER_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_MANAGER_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_MANAGER_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_manager *ovsrec_manager_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_manager *ovsrec_manager_table_get_for_uuid(const struct ovsrec_manager_table *, const struct uuid *);
const struct ovsrec_manager *ovsrec_manager_first(const struct ovsdb_idl *);
const struct ovsrec_manager *ovsrec_manager_next(const struct ovsrec_manager *);
#define OVSREC_MANAGER_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_manager_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_manager_next(ROW))
#define OVSREC_MANAGER_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_manager_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_manager_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_MANAGER_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_manager * ROW__next = ((ROW) = ovsrec_manager_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_manager_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_MANAGER_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_MANAGER_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_MANAGER_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_manager_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_manager_row_get_seqno(const struct ovsrec_manager *row, enum ovsdb_idl_change change);
const struct ovsrec_manager *ovsrec_manager_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_manager *ovsrec_manager_track_get_next(const struct ovsrec_manager *);
#define OVSREC_MANAGER_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_manager_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_manager_track_get_next(ROW))

const struct ovsrec_manager *ovsrec_manager_table_track_get_first(const struct ovsrec_manager_table *);
#define OVSREC_MANAGER_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_manager_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_manager_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_manager_is_new(const struct ovsrec_manager *row)
{
    return ovsrec_manager_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_manager_is_deleted(const struct ovsrec_manager *row)
{
    return ovsrec_manager_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_manager_index_destroy_row(const struct ovsrec_manager *);

struct ovsrec_manager *ovsrec_manager_index_find(struct ovsdb_idl_index *, const struct ovsrec_manager *);

int ovsrec_manager_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_manager *, 
    const struct ovsrec_manager *);
struct ovsdb_idl_cursor ovsrec_manager_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_manager_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_manager *);
struct ovsdb_idl_cursor ovsrec_manager_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_manager *);

struct ovsrec_manager *ovsrec_manager_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_MANAGER_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_manager_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_manager_cursor_data(&cursor__), \
                  !(TO) || ovsrec_manager_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_MANAGER_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_manager_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_manager_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_MANAGER_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_manager_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_manager_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_manager_init(struct ovsrec_manager *);
void ovsrec_manager_delete(const struct ovsrec_manager *);
struct ovsrec_manager *ovsrec_manager_insert(struct ovsdb_idl_txn *);
struct ovsrec_manager *ovsrec_manager_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_manager_column_id' of
 * the row referenced by 'struct ovsrec_manager *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_manager_is_updated(const struct ovsrec_manager *, enum ovsrec_manager_column_id);

void ovsrec_manager_verify_connection_mode(const struct ovsrec_manager *);
void ovsrec_manager_verify_external_ids(const struct ovsrec_manager *);
void ovsrec_manager_verify_inactivity_probe(const struct ovsrec_manager *);
void ovsrec_manager_verify_is_connected(const struct ovsrec_manager *);
void ovsrec_manager_verify_max_backoff(const struct ovsrec_manager *);
void ovsrec_manager_verify_other_config(const struct ovsrec_manager *);
void ovsrec_manager_verify_status(const struct ovsrec_manager *);
void ovsrec_manager_verify_target(const struct ovsrec_manager *);

const struct ovsdb_datum *ovsrec_manager_get_connection_mode(const struct ovsrec_manager *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_manager_get_external_ids(const struct ovsrec_manager *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_manager_get_inactivity_probe(const struct ovsrec_manager *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_manager_get_is_connected(const struct ovsrec_manager *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_manager_get_max_backoff(const struct ovsrec_manager *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_manager_get_other_config(const struct ovsrec_manager *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_manager_get_status(const struct ovsrec_manager *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_manager_get_target(const struct ovsrec_manager *, enum ovsdb_atomic_type key_type);

void ovsrec_manager_set_connection_mode(const struct ovsrec_manager *, const char *connection_mode);
void ovsrec_manager_set_external_ids(const struct ovsrec_manager *, const struct smap *);
void ovsrec_manager_set_inactivity_probe(const struct ovsrec_manager *, const int64_t *inactivity_probe, size_t n_inactivity_probe);
void ovsrec_manager_set_is_connected(const struct ovsrec_manager *, bool is_connected);
void ovsrec_manager_set_max_backoff(const struct ovsrec_manager *, const int64_t *max_backoff, size_t n_max_backoff);
void ovsrec_manager_set_other_config(const struct ovsrec_manager *, const struct smap *);
void ovsrec_manager_set_status(const struct ovsrec_manager *, const struct smap *);
void ovsrec_manager_set_target(const struct ovsrec_manager *, const char *target);

void ovsrec_manager_update_connection_mode_addvalue(const struct ovsrec_manager *,  const char *);
void ovsrec_manager_update_connection_mode_delvalue(const struct ovsrec_manager *,  const char *);
void ovsrec_manager_add_clause_connection_mode(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *connection_mode);
unsigned int ovsrec_manager_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_manager_update_external_ids_setkey(const struct ovsrec_manager *,  const char *, const char *);
void ovsrec_manager_update_external_ids_delkey(const struct ovsrec_manager *,  const char *);
void ovsrec_manager_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_manager_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_manager_update_inactivity_probe_addvalue(const struct ovsrec_manager *,  int64_t );
void ovsrec_manager_update_inactivity_probe_delvalue(const struct ovsrec_manager *,  int64_t );
void ovsrec_manager_add_clause_inactivity_probe(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *inactivity_probe, size_t n_inactivity_probe);
unsigned int ovsrec_manager_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_manager_add_clause_is_connected(struct ovsdb_idl_condition *, enum ovsdb_function function, bool is_connected);
unsigned int ovsrec_manager_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_manager_update_max_backoff_addvalue(const struct ovsrec_manager *,  int64_t );
void ovsrec_manager_update_max_backoff_delvalue(const struct ovsrec_manager *,  int64_t );
void ovsrec_manager_add_clause_max_backoff(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *max_backoff, size_t n_max_backoff);
unsigned int ovsrec_manager_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_manager_update_other_config_setkey(const struct ovsrec_manager *,  const char *, const char *);
void ovsrec_manager_update_other_config_delkey(const struct ovsrec_manager *,  const char *);
void ovsrec_manager_add_clause_other_config(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_manager_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_manager_update_status_setkey(const struct ovsrec_manager *,  const char *, const char *);
void ovsrec_manager_update_status_delkey(const struct ovsrec_manager *,  const char *);
void ovsrec_manager_add_clause_status(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_manager_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_manager_add_clause_target(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *target);
unsigned int ovsrec_manager_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_manager *ovsrec_manager_index_init_row(struct ovsdb_idl_index *);
void ovsrec_manager_index_set_connection_mode(const struct ovsrec_manager *,
const char *connection_mode);
void ovsrec_manager_index_set_external_ids(const struct ovsrec_manager *,
const struct smap *);
void ovsrec_manager_index_set_inactivity_probe(const struct ovsrec_manager *,
const int64_t *inactivity_probe, size_t n_inactivity_probe);
void ovsrec_manager_index_set_is_connected(const struct ovsrec_manager *,
bool is_connected);
void ovsrec_manager_index_set_max_backoff(const struct ovsrec_manager *,
const int64_t *max_backoff, size_t n_max_backoff);
void ovsrec_manager_index_set_other_config(const struct ovsrec_manager *,
const struct smap *);
void ovsrec_manager_index_set_status(const struct ovsrec_manager *,
const struct smap *);
void ovsrec_manager_index_set_target(const struct ovsrec_manager *,
const char *target);

/* Mirror table. */
struct ovsrec_mirror {
	struct ovsdb_idl_row header_;

	/* external_ids column. */
	struct smap external_ids;

	/* name column. */
	char *name;	/* Always nonnull. */

	/* output_port column. */
	struct ovsrec_port *output_port;

	/* output_vlan column. */
	int64_t *output_vlan;
	size_t n_output_vlan;

	/* select_all column. */
	bool select_all;

	/* select_dst_port column. */
	struct ovsrec_port **select_dst_port;
	size_t n_select_dst_port;

	/* select_src_port column. */
	struct ovsrec_port **select_src_port;
	size_t n_select_src_port;

	/* select_vlan column. */
	int64_t *select_vlan;
	size_t n_select_vlan;

	/* snaplen column. */
	int64_t *snaplen;
	size_t n_snaplen;

	/* statistics column. */
	char **key_statistics;
	int64_t *value_statistics;
	size_t n_statistics;
};

enum ovsrec_mirror_column_id {
    OVSREC_MIRROR_COL_EXTERNAL_IDS,
    OVSREC_MIRROR_COL_NAME,
    OVSREC_MIRROR_COL_OUTPUT_PORT,
    OVSREC_MIRROR_COL_OUTPUT_VLAN,
    OVSREC_MIRROR_COL_SELECT_ALL,
    OVSREC_MIRROR_COL_SELECT_DST_PORT,
    OVSREC_MIRROR_COL_SELECT_SRC_PORT,
    OVSREC_MIRROR_COL_SELECT_VLAN,
    OVSREC_MIRROR_COL_SNAPLEN,
    OVSREC_MIRROR_COL_STATISTICS,
    OVSREC_MIRROR_N_COLUMNS
};

#define ovsrec_mirror_col_external_ids (ovsrec_mirror_columns[OVSREC_MIRROR_COL_EXTERNAL_IDS])
#define ovsrec_mirror_col_name (ovsrec_mirror_columns[OVSREC_MIRROR_COL_NAME])
#define ovsrec_mirror_col_output_port (ovsrec_mirror_columns[OVSREC_MIRROR_COL_OUTPUT_PORT])
#define ovsrec_mirror_col_output_vlan (ovsrec_mirror_columns[OVSREC_MIRROR_COL_OUTPUT_VLAN])
#define ovsrec_mirror_col_select_all (ovsrec_mirror_columns[OVSREC_MIRROR_COL_SELECT_ALL])
#define ovsrec_mirror_col_select_dst_port (ovsrec_mirror_columns[OVSREC_MIRROR_COL_SELECT_DST_PORT])
#define ovsrec_mirror_col_select_src_port (ovsrec_mirror_columns[OVSREC_MIRROR_COL_SELECT_SRC_PORT])
#define ovsrec_mirror_col_select_vlan (ovsrec_mirror_columns[OVSREC_MIRROR_COL_SELECT_VLAN])
#define ovsrec_mirror_col_snaplen (ovsrec_mirror_columns[OVSREC_MIRROR_COL_SNAPLEN])
#define ovsrec_mirror_col_statistics (ovsrec_mirror_columns[OVSREC_MIRROR_COL_STATISTICS])

extern struct ovsdb_idl_column ovsrec_mirror_columns[OVSREC_MIRROR_N_COLUMNS];
bool ovsrec_server_has_mirror_table_col_external_ids(const struct ovsdb_idl *); 
bool ovsrec_server_has_mirror_table_col_name(const struct ovsdb_idl *); 
bool ovsrec_server_has_mirror_table_col_output_port(const struct ovsdb_idl *); 
bool ovsrec_server_has_mirror_table_col_output_vlan(const struct ovsdb_idl *); 
bool ovsrec_server_has_mirror_table_col_select_all(const struct ovsdb_idl *); 
bool ovsrec_server_has_mirror_table_col_select_dst_port(const struct ovsdb_idl *); 
bool ovsrec_server_has_mirror_table_col_select_src_port(const struct ovsdb_idl *); 
bool ovsrec_server_has_mirror_table_col_select_vlan(const struct ovsdb_idl *); 
bool ovsrec_server_has_mirror_table_col_snaplen(const struct ovsdb_idl *); 
bool ovsrec_server_has_mirror_table_col_statistics(const struct ovsdb_idl *); 

bool ovsrec_server_has_mirror_table(const struct ovsdb_idl *);
const struct ovsrec_mirror_table *ovsrec_mirror_table_get(const struct ovsdb_idl *);
const struct ovsrec_mirror *ovsrec_mirror_table_first(const struct ovsrec_mirror_table *);

#define OVSREC_MIRROR_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_mirror_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_mirror_next(ROW))
#define OVSREC_MIRROR_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_mirror_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_mirror_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_MIRROR_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_mirror * ROW__next = ((ROW) = ovsrec_mirror_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_mirror_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_MIRROR_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_MIRROR_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_MIRROR_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_mirror *ovsrec_mirror_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_mirror *ovsrec_mirror_table_get_for_uuid(const struct ovsrec_mirror_table *, const struct uuid *);
const struct ovsrec_mirror *ovsrec_mirror_first(const struct ovsdb_idl *);
const struct ovsrec_mirror *ovsrec_mirror_next(const struct ovsrec_mirror *);
#define OVSREC_MIRROR_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_mirror_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_mirror_next(ROW))
#define OVSREC_MIRROR_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_mirror_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_mirror_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_MIRROR_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_mirror * ROW__next = ((ROW) = ovsrec_mirror_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_mirror_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_MIRROR_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_MIRROR_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_MIRROR_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_mirror_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_mirror_row_get_seqno(const struct ovsrec_mirror *row, enum ovsdb_idl_change change);
const struct ovsrec_mirror *ovsrec_mirror_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_mirror *ovsrec_mirror_track_get_next(const struct ovsrec_mirror *);
#define OVSREC_MIRROR_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_mirror_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_mirror_track_get_next(ROW))

const struct ovsrec_mirror *ovsrec_mirror_table_track_get_first(const struct ovsrec_mirror_table *);
#define OVSREC_MIRROR_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_mirror_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_mirror_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_mirror_is_new(const struct ovsrec_mirror *row)
{
    return ovsrec_mirror_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_mirror_is_deleted(const struct ovsrec_mirror *row)
{
    return ovsrec_mirror_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_mirror_index_destroy_row(const struct ovsrec_mirror *);

struct ovsrec_mirror *ovsrec_mirror_index_find(struct ovsdb_idl_index *, const struct ovsrec_mirror *);

int ovsrec_mirror_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_mirror *, 
    const struct ovsrec_mirror *);
struct ovsdb_idl_cursor ovsrec_mirror_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_mirror_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_mirror *);
struct ovsdb_idl_cursor ovsrec_mirror_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_mirror *);

struct ovsrec_mirror *ovsrec_mirror_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_MIRROR_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_mirror_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_mirror_cursor_data(&cursor__), \
                  !(TO) || ovsrec_mirror_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_MIRROR_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_mirror_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_mirror_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_MIRROR_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_mirror_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_mirror_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_mirror_init(struct ovsrec_mirror *);
void ovsrec_mirror_delete(const struct ovsrec_mirror *);
struct ovsrec_mirror *ovsrec_mirror_insert(struct ovsdb_idl_txn *);
struct ovsrec_mirror *ovsrec_mirror_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_mirror_column_id' of
 * the row referenced by 'struct ovsrec_mirror *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_mirror_is_updated(const struct ovsrec_mirror *, enum ovsrec_mirror_column_id);

void ovsrec_mirror_verify_external_ids(const struct ovsrec_mirror *);
void ovsrec_mirror_verify_name(const struct ovsrec_mirror *);
void ovsrec_mirror_verify_output_port(const struct ovsrec_mirror *);
void ovsrec_mirror_verify_output_vlan(const struct ovsrec_mirror *);
void ovsrec_mirror_verify_select_all(const struct ovsrec_mirror *);
void ovsrec_mirror_verify_select_dst_port(const struct ovsrec_mirror *);
void ovsrec_mirror_verify_select_src_port(const struct ovsrec_mirror *);
void ovsrec_mirror_verify_select_vlan(const struct ovsrec_mirror *);
void ovsrec_mirror_verify_snaplen(const struct ovsrec_mirror *);
void ovsrec_mirror_verify_statistics(const struct ovsrec_mirror *);

const struct ovsdb_datum *ovsrec_mirror_get_external_ids(const struct ovsrec_mirror *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_mirror_get_name(const struct ovsrec_mirror *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_mirror_get_output_port(const struct ovsrec_mirror *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_mirror_get_output_vlan(const struct ovsrec_mirror *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_mirror_get_select_all(const struct ovsrec_mirror *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_mirror_get_select_dst_port(const struct ovsrec_mirror *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_mirror_get_select_src_port(const struct ovsrec_mirror *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_mirror_get_select_vlan(const struct ovsrec_mirror *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_mirror_get_snaplen(const struct ovsrec_mirror *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_mirror_get_statistics(const struct ovsrec_mirror *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);

void ovsrec_mirror_set_external_ids(const struct ovsrec_mirror *, const struct smap *);
void ovsrec_mirror_set_name(const struct ovsrec_mirror *, const char *name);
void ovsrec_mirror_set_output_port(const struct ovsrec_mirror *, const struct ovsrec_port *output_port);
void ovsrec_mirror_set_output_vlan(const struct ovsrec_mirror *, const int64_t *output_vlan, size_t n_output_vlan);
void ovsrec_mirror_set_select_all(const struct ovsrec_mirror *, bool select_all);
void ovsrec_mirror_set_select_dst_port(const struct ovsrec_mirror *, struct ovsrec_port **select_dst_port, size_t n_select_dst_port);
void ovsrec_mirror_set_select_src_port(const struct ovsrec_mirror *, struct ovsrec_port **select_src_port, size_t n_select_src_port);
void ovsrec_mirror_set_select_vlan(const struct ovsrec_mirror *, const int64_t *select_vlan, size_t n_select_vlan);
void ovsrec_mirror_set_snaplen(const struct ovsrec_mirror *, const int64_t *snaplen, size_t n_snaplen);
void ovsrec_mirror_set_statistics(const struct ovsrec_mirror *, const char **key_statistics, const int64_t *value_statistics, size_t n_statistics);

void ovsrec_mirror_update_external_ids_setkey(const struct ovsrec_mirror *,  const char *, const char *);
void ovsrec_mirror_update_external_ids_delkey(const struct ovsrec_mirror *,  const char *);
void ovsrec_mirror_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_mirror_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_mirror_add_clause_name(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *name);
unsigned int ovsrec_mirror_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_mirror_update_output_port_addvalue(const struct ovsrec_mirror *,  const struct ovsrec_port *);
void ovsrec_mirror_update_output_port_delvalue(const struct ovsrec_mirror *,  const struct ovsrec_port *);
void ovsrec_mirror_add_clause_output_port(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct uuid *output_port);
unsigned int ovsrec_mirror_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_mirror_update_output_vlan_addvalue(const struct ovsrec_mirror *,  int64_t );
void ovsrec_mirror_update_output_vlan_delvalue(const struct ovsrec_mirror *,  int64_t );
void ovsrec_mirror_add_clause_output_vlan(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *output_vlan, size_t n_output_vlan);
unsigned int ovsrec_mirror_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_mirror_add_clause_select_all(struct ovsdb_idl_condition *, enum ovsdb_function function, bool select_all);
unsigned int ovsrec_mirror_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_mirror_update_select_dst_port_addvalue(const struct ovsrec_mirror *,  const struct ovsrec_port *);
void ovsrec_mirror_update_select_dst_port_delvalue(const struct ovsrec_mirror *,  const struct ovsrec_port *);
void ovsrec_mirror_add_clause_select_dst_port(struct ovsdb_idl_condition *, enum ovsdb_function function, struct uuid **select_dst_port, size_t n_select_dst_port);
unsigned int ovsrec_mirror_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_mirror_update_select_src_port_addvalue(const struct ovsrec_mirror *,  const struct ovsrec_port *);
void ovsrec_mirror_update_select_src_port_delvalue(const struct ovsrec_mirror *,  const struct ovsrec_port *);
void ovsrec_mirror_add_clause_select_src_port(struct ovsdb_idl_condition *, enum ovsdb_function function, struct uuid **select_src_port, size_t n_select_src_port);
unsigned int ovsrec_mirror_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_mirror_update_select_vlan_addvalue(const struct ovsrec_mirror *,  int64_t );
void ovsrec_mirror_update_select_vlan_delvalue(const struct ovsrec_mirror *,  int64_t );
void ovsrec_mirror_add_clause_select_vlan(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *select_vlan, size_t n_select_vlan);
unsigned int ovsrec_mirror_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_mirror_update_snaplen_addvalue(const struct ovsrec_mirror *,  int64_t );
void ovsrec_mirror_update_snaplen_delvalue(const struct ovsrec_mirror *,  int64_t );
void ovsrec_mirror_add_clause_snaplen(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *snaplen, size_t n_snaplen);
unsigned int ovsrec_mirror_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_mirror_update_statistics_setkey(const struct ovsrec_mirror *,  const char *, int64_t );
void ovsrec_mirror_update_statistics_delkey(const struct ovsrec_mirror *,  const char *);
void ovsrec_mirror_add_clause_statistics(struct ovsdb_idl_condition *, enum ovsdb_function function, const char **key_statistics, const int64_t *value_statistics, size_t n_statistics);
unsigned int ovsrec_mirror_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_mirror *ovsrec_mirror_index_init_row(struct ovsdb_idl_index *);
void ovsrec_mirror_index_set_external_ids(const struct ovsrec_mirror *,
const struct smap *);
void ovsrec_mirror_index_set_name(const struct ovsrec_mirror *,
const char *name);
void ovsrec_mirror_index_set_output_port(const struct ovsrec_mirror *,
const struct ovsrec_port *output_port);
void ovsrec_mirror_index_set_output_vlan(const struct ovsrec_mirror *,
const int64_t *output_vlan, size_t n_output_vlan);
void ovsrec_mirror_index_set_select_all(const struct ovsrec_mirror *,
bool select_all);
void ovsrec_mirror_index_set_select_dst_port(const struct ovsrec_mirror *,
struct ovsrec_port **select_dst_port, size_t n_select_dst_port);
void ovsrec_mirror_index_set_select_src_port(const struct ovsrec_mirror *,
struct ovsrec_port **select_src_port, size_t n_select_src_port);
void ovsrec_mirror_index_set_select_vlan(const struct ovsrec_mirror *,
const int64_t *select_vlan, size_t n_select_vlan);
void ovsrec_mirror_index_set_snaplen(const struct ovsrec_mirror *,
const int64_t *snaplen, size_t n_snaplen);
void ovsrec_mirror_index_set_statistics(const struct ovsrec_mirror *,
const char **key_statistics, const int64_t *value_statistics, size_t n_statistics);

/* NetFlow table. */
struct ovsrec_netflow {
	struct ovsdb_idl_row header_;

	/* active_timeout column. */
	int64_t active_timeout;

	/* add_id_to_interface column. */
	bool add_id_to_interface;

	/* engine_id column. */
	int64_t *engine_id;
	size_t n_engine_id;

	/* engine_type column. */
	int64_t *engine_type;
	size_t n_engine_type;

	/* external_ids column. */
	struct smap external_ids;

	/* targets column. */
	char **targets;
	size_t n_targets;
};

enum ovsrec_netflow_column_id {
    OVSREC_NETFLOW_COL_ACTIVE_TIMEOUT,
    OVSREC_NETFLOW_COL_ADD_ID_TO_INTERFACE,
    OVSREC_NETFLOW_COL_ENGINE_ID,
    OVSREC_NETFLOW_COL_ENGINE_TYPE,
    OVSREC_NETFLOW_COL_EXTERNAL_IDS,
    OVSREC_NETFLOW_COL_TARGETS,
    OVSREC_NETFLOW_N_COLUMNS
};

#define ovsrec_netflow_col_active_timeout (ovsrec_netflow_columns[OVSREC_NETFLOW_COL_ACTIVE_TIMEOUT])
#define ovsrec_netflow_col_add_id_to_interface (ovsrec_netflow_columns[OVSREC_NETFLOW_COL_ADD_ID_TO_INTERFACE])
#define ovsrec_netflow_col_engine_id (ovsrec_netflow_columns[OVSREC_NETFLOW_COL_ENGINE_ID])
#define ovsrec_netflow_col_engine_type (ovsrec_netflow_columns[OVSREC_NETFLOW_COL_ENGINE_TYPE])
#define ovsrec_netflow_col_external_ids (ovsrec_netflow_columns[OVSREC_NETFLOW_COL_EXTERNAL_IDS])
#define ovsrec_netflow_col_targets (ovsrec_netflow_columns[OVSREC_NETFLOW_COL_TARGETS])

extern struct ovsdb_idl_column ovsrec_netflow_columns[OVSREC_NETFLOW_N_COLUMNS];
bool ovsrec_server_has_netflow_table_col_active_timeout(const struct ovsdb_idl *); 
bool ovsrec_server_has_netflow_table_col_add_id_to_interface(const struct ovsdb_idl *); 
bool ovsrec_server_has_netflow_table_col_engine_id(const struct ovsdb_idl *); 
bool ovsrec_server_has_netflow_table_col_engine_type(const struct ovsdb_idl *); 
bool ovsrec_server_has_netflow_table_col_external_ids(const struct ovsdb_idl *); 
bool ovsrec_server_has_netflow_table_col_targets(const struct ovsdb_idl *); 

bool ovsrec_server_has_netflow_table(const struct ovsdb_idl *);
const struct ovsrec_netflow_table *ovsrec_netflow_table_get(const struct ovsdb_idl *);
const struct ovsrec_netflow *ovsrec_netflow_table_first(const struct ovsrec_netflow_table *);

#define OVSREC_NETFLOW_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_netflow_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_netflow_next(ROW))
#define OVSREC_NETFLOW_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_netflow_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_netflow_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_NETFLOW_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_netflow * ROW__next = ((ROW) = ovsrec_netflow_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_netflow_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_NETFLOW_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_NETFLOW_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_NETFLOW_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_netflow *ovsrec_netflow_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_netflow *ovsrec_netflow_table_get_for_uuid(const struct ovsrec_netflow_table *, const struct uuid *);
const struct ovsrec_netflow *ovsrec_netflow_first(const struct ovsdb_idl *);
const struct ovsrec_netflow *ovsrec_netflow_next(const struct ovsrec_netflow *);
#define OVSREC_NETFLOW_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_netflow_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_netflow_next(ROW))
#define OVSREC_NETFLOW_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_netflow_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_netflow_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_NETFLOW_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_netflow * ROW__next = ((ROW) = ovsrec_netflow_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_netflow_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_NETFLOW_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_NETFLOW_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_NETFLOW_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_netflow_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_netflow_row_get_seqno(const struct ovsrec_netflow *row, enum ovsdb_idl_change change);
const struct ovsrec_netflow *ovsrec_netflow_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_netflow *ovsrec_netflow_track_get_next(const struct ovsrec_netflow *);
#define OVSREC_NETFLOW_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_netflow_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_netflow_track_get_next(ROW))

const struct ovsrec_netflow *ovsrec_netflow_table_track_get_first(const struct ovsrec_netflow_table *);
#define OVSREC_NETFLOW_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_netflow_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_netflow_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_netflow_is_new(const struct ovsrec_netflow *row)
{
    return ovsrec_netflow_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_netflow_is_deleted(const struct ovsrec_netflow *row)
{
    return ovsrec_netflow_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_netflow_index_destroy_row(const struct ovsrec_netflow *);

struct ovsrec_netflow *ovsrec_netflow_index_find(struct ovsdb_idl_index *, const struct ovsrec_netflow *);

int ovsrec_netflow_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_netflow *, 
    const struct ovsrec_netflow *);
struct ovsdb_idl_cursor ovsrec_netflow_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_netflow_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_netflow *);
struct ovsdb_idl_cursor ovsrec_netflow_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_netflow *);

struct ovsrec_netflow *ovsrec_netflow_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_NETFLOW_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_netflow_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_netflow_cursor_data(&cursor__), \
                  !(TO) || ovsrec_netflow_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_NETFLOW_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_netflow_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_netflow_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_NETFLOW_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_netflow_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_netflow_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_netflow_init(struct ovsrec_netflow *);
void ovsrec_netflow_delete(const struct ovsrec_netflow *);
struct ovsrec_netflow *ovsrec_netflow_insert(struct ovsdb_idl_txn *);
struct ovsrec_netflow *ovsrec_netflow_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_netflow_column_id' of
 * the row referenced by 'struct ovsrec_netflow *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_netflow_is_updated(const struct ovsrec_netflow *, enum ovsrec_netflow_column_id);

void ovsrec_netflow_verify_active_timeout(const struct ovsrec_netflow *);
void ovsrec_netflow_verify_add_id_to_interface(const struct ovsrec_netflow *);
void ovsrec_netflow_verify_engine_id(const struct ovsrec_netflow *);
void ovsrec_netflow_verify_engine_type(const struct ovsrec_netflow *);
void ovsrec_netflow_verify_external_ids(const struct ovsrec_netflow *);
void ovsrec_netflow_verify_targets(const struct ovsrec_netflow *);

const struct ovsdb_datum *ovsrec_netflow_get_active_timeout(const struct ovsrec_netflow *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_netflow_get_add_id_to_interface(const struct ovsrec_netflow *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_netflow_get_engine_id(const struct ovsrec_netflow *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_netflow_get_engine_type(const struct ovsrec_netflow *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_netflow_get_external_ids(const struct ovsrec_netflow *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_netflow_get_targets(const struct ovsrec_netflow *, enum ovsdb_atomic_type key_type);

void ovsrec_netflow_set_active_timeout(const struct ovsrec_netflow *, int64_t active_timeout);
void ovsrec_netflow_set_add_id_to_interface(const struct ovsrec_netflow *, bool add_id_to_interface);
void ovsrec_netflow_set_engine_id(const struct ovsrec_netflow *, const int64_t *engine_id, size_t n_engine_id);
void ovsrec_netflow_set_engine_type(const struct ovsrec_netflow *, const int64_t *engine_type, size_t n_engine_type);
void ovsrec_netflow_set_external_ids(const struct ovsrec_netflow *, const struct smap *);
void ovsrec_netflow_set_targets(const struct ovsrec_netflow *, const char **targets, size_t n_targets);

void ovsrec_netflow_add_clause_active_timeout(struct ovsdb_idl_condition *, enum ovsdb_function function, int64_t active_timeout);
unsigned int ovsrec_netflow_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_netflow_add_clause_add_id_to_interface(struct ovsdb_idl_condition *, enum ovsdb_function function, bool add_id_to_interface);
unsigned int ovsrec_netflow_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_netflow_update_engine_id_addvalue(const struct ovsrec_netflow *,  int64_t );
void ovsrec_netflow_update_engine_id_delvalue(const struct ovsrec_netflow *,  int64_t );
void ovsrec_netflow_add_clause_engine_id(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *engine_id, size_t n_engine_id);
unsigned int ovsrec_netflow_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_netflow_update_engine_type_addvalue(const struct ovsrec_netflow *,  int64_t );
void ovsrec_netflow_update_engine_type_delvalue(const struct ovsrec_netflow *,  int64_t );
void ovsrec_netflow_add_clause_engine_type(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *engine_type, size_t n_engine_type);
unsigned int ovsrec_netflow_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_netflow_update_external_ids_setkey(const struct ovsrec_netflow *,  const char *, const char *);
void ovsrec_netflow_update_external_ids_delkey(const struct ovsrec_netflow *,  const char *);
void ovsrec_netflow_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_netflow_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_netflow_update_targets_addvalue(const struct ovsrec_netflow *,  const char *);
void ovsrec_netflow_update_targets_delvalue(const struct ovsrec_netflow *,  const char *);
void ovsrec_netflow_add_clause_targets(struct ovsdb_idl_condition *, enum ovsdb_function function, const char **targets, size_t n_targets);
unsigned int ovsrec_netflow_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_netflow *ovsrec_netflow_index_init_row(struct ovsdb_idl_index *);
void ovsrec_netflow_index_set_active_timeout(const struct ovsrec_netflow *,
int64_t active_timeout);
void ovsrec_netflow_index_set_add_id_to_interface(const struct ovsrec_netflow *,
bool add_id_to_interface);
void ovsrec_netflow_index_set_engine_id(const struct ovsrec_netflow *,
const int64_t *engine_id, size_t n_engine_id);
void ovsrec_netflow_index_set_engine_type(const struct ovsrec_netflow *,
const int64_t *engine_type, size_t n_engine_type);
void ovsrec_netflow_index_set_external_ids(const struct ovsrec_netflow *,
const struct smap *);
void ovsrec_netflow_index_set_targets(const struct ovsrec_netflow *,
const char **targets, size_t n_targets);

/* Open_vSwitch table. */
struct ovsrec_open_vswitch {
	struct ovsdb_idl_row header_;

	/* bridges column. */
	struct ovsrec_bridge **bridges;
	size_t n_bridges;

	/* cur_cfg column. */
	int64_t cur_cfg;

	/* datapath_types column. */
	char **datapath_types;
	size_t n_datapath_types;

	/* datapaths column. */
	char **key_datapaths;
	struct ovsrec_datapath **value_datapaths;
	size_t n_datapaths;

	/* db_version column. */
	char *db_version;

	/* dpdk_initialized column. */
	bool dpdk_initialized;

	/* dpdk_version column. */
	char *dpdk_version;

	/* external_ids column. */
	struct smap external_ids;

	/* iface_types column. */
	char **iface_types;
	size_t n_iface_types;

	/* manager_options column. */
	struct ovsrec_manager **manager_options;
	size_t n_manager_options;

	/* next_cfg column. */
	int64_t next_cfg;

	/* other_config column. */
	struct smap other_config;

	/* ovs_version column. */
	char *ovs_version;

	/* ssl column. */
	struct ovsrec_ssl *ssl;

	/* statistics column. */
	struct smap statistics;

	/* system_type column. */
	char *system_type;

	/* system_version column. */
	char *system_version;
};

enum ovsrec_open_vswitch_column_id {
    OVSREC_OPEN_VSWITCH_COL_BRIDGES,
    OVSREC_OPEN_VSWITCH_COL_CUR_CFG,
    OVSREC_OPEN_VSWITCH_COL_DATAPATH_TYPES,
    OVSREC_OPEN_VSWITCH_COL_DATAPATHS,
    OVSREC_OPEN_VSWITCH_COL_DB_VERSION,
    OVSREC_OPEN_VSWITCH_COL_DPDK_INITIALIZED,
    OVSREC_OPEN_VSWITCH_COL_DPDK_VERSION,
    OVSREC_OPEN_VSWITCH_COL_EXTERNAL_IDS,
    OVSREC_OPEN_VSWITCH_COL_IFACE_TYPES,
    OVSREC_OPEN_VSWITCH_COL_MANAGER_OPTIONS,
    OVSREC_OPEN_VSWITCH_COL_NEXT_CFG,
    OVSREC_OPEN_VSWITCH_COL_OTHER_CONFIG,
    OVSREC_OPEN_VSWITCH_COL_OVS_VERSION,
    OVSREC_OPEN_VSWITCH_COL_SSL,
    OVSREC_OPEN_VSWITCH_COL_STATISTICS,
    OVSREC_OPEN_VSWITCH_COL_SYSTEM_TYPE,
    OVSREC_OPEN_VSWITCH_COL_SYSTEM_VERSION,
    OVSREC_OPEN_VSWITCH_N_COLUMNS
};

#define ovsrec_open_vswitch_col_bridges (ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_COL_BRIDGES])
#define ovsrec_open_vswitch_col_cur_cfg (ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_COL_CUR_CFG])
#define ovsrec_open_vswitch_col_datapath_types (ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_COL_DATAPATH_TYPES])
#define ovsrec_open_vswitch_col_datapaths (ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_COL_DATAPATHS])
#define ovsrec_open_vswitch_col_db_version (ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_COL_DB_VERSION])
#define ovsrec_open_vswitch_col_dpdk_initialized (ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_COL_DPDK_INITIALIZED])
#define ovsrec_open_vswitch_col_dpdk_version (ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_COL_DPDK_VERSION])
#define ovsrec_open_vswitch_col_external_ids (ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_COL_EXTERNAL_IDS])
#define ovsrec_open_vswitch_col_iface_types (ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_COL_IFACE_TYPES])
#define ovsrec_open_vswitch_col_manager_options (ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_COL_MANAGER_OPTIONS])
#define ovsrec_open_vswitch_col_next_cfg (ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_COL_NEXT_CFG])
#define ovsrec_open_vswitch_col_other_config (ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_COL_OTHER_CONFIG])
#define ovsrec_open_vswitch_col_ovs_version (ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_COL_OVS_VERSION])
#define ovsrec_open_vswitch_col_ssl (ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_COL_SSL])
#define ovsrec_open_vswitch_col_statistics (ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_COL_STATISTICS])
#define ovsrec_open_vswitch_col_system_type (ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_COL_SYSTEM_TYPE])
#define ovsrec_open_vswitch_col_system_version (ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_COL_SYSTEM_VERSION])

extern struct ovsdb_idl_column ovsrec_open_vswitch_columns[OVSREC_OPEN_VSWITCH_N_COLUMNS];
bool ovsrec_server_has_open_vswitch_table_col_bridges(const struct ovsdb_idl *); 
bool ovsrec_server_has_open_vswitch_table_col_cur_cfg(const struct ovsdb_idl *); 
bool ovsrec_server_has_open_vswitch_table_col_datapath_types(const struct ovsdb_idl *); 
bool ovsrec_server_has_open_vswitch_table_col_datapaths(const struct ovsdb_idl *); 
bool ovsrec_server_has_open_vswitch_table_col_db_version(const struct ovsdb_idl *); 
bool ovsrec_server_has_open_vswitch_table_col_dpdk_initialized(const struct ovsdb_idl *); 
bool ovsrec_server_has_open_vswitch_table_col_dpdk_version(const struct ovsdb_idl *); 
bool ovsrec_server_has_open_vswitch_table_col_external_ids(const struct ovsdb_idl *); 
bool ovsrec_server_has_open_vswitch_table_col_iface_types(const struct ovsdb_idl *); 
bool ovsrec_server_has_open_vswitch_table_col_manager_options(const struct ovsdb_idl *); 
bool ovsrec_server_has_open_vswitch_table_col_next_cfg(const struct ovsdb_idl *); 
bool ovsrec_server_has_open_vswitch_table_col_other_config(const struct ovsdb_idl *); 
bool ovsrec_server_has_open_vswitch_table_col_ovs_version(const struct ovsdb_idl *); 
bool ovsrec_server_has_open_vswitch_table_col_ssl(const struct ovsdb_idl *); 
bool ovsrec_server_has_open_vswitch_table_col_statistics(const struct ovsdb_idl *); 
bool ovsrec_server_has_open_vswitch_table_col_system_type(const struct ovsdb_idl *); 
bool ovsrec_server_has_open_vswitch_table_col_system_version(const struct ovsdb_idl *); 

bool ovsrec_server_has_open_vswitch_table(const struct ovsdb_idl *);
const struct ovsrec_open_vswitch_table *ovsrec_open_vswitch_table_get(const struct ovsdb_idl *);
const struct ovsrec_open_vswitch *ovsrec_open_vswitch_table_first(const struct ovsrec_open_vswitch_table *);

#define OVSREC_OPEN_VSWITCH_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_open_vswitch_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_open_vswitch_next(ROW))
#define OVSREC_OPEN_VSWITCH_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_open_vswitch_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_open_vswitch_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_OPEN_VSWITCH_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_open_vswitch * ROW__next = ((ROW) = ovsrec_open_vswitch_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_open_vswitch_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_OPEN_VSWITCH_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_OPEN_VSWITCH_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_OPEN_VSWITCH_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_open_vswitch *ovsrec_open_vswitch_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_open_vswitch *ovsrec_open_vswitch_table_get_for_uuid(const struct ovsrec_open_vswitch_table *, const struct uuid *);
const struct ovsrec_open_vswitch *ovsrec_open_vswitch_first(const struct ovsdb_idl *);
const struct ovsrec_open_vswitch *ovsrec_open_vswitch_next(const struct ovsrec_open_vswitch *);
#define OVSREC_OPEN_VSWITCH_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_open_vswitch_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_open_vswitch_next(ROW))
#define OVSREC_OPEN_VSWITCH_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_open_vswitch_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_open_vswitch_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_OPEN_VSWITCH_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_open_vswitch * ROW__next = ((ROW) = ovsrec_open_vswitch_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_open_vswitch_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_OPEN_VSWITCH_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_OPEN_VSWITCH_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_OPEN_VSWITCH_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_open_vswitch_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_open_vswitch_row_get_seqno(const struct ovsrec_open_vswitch *row, enum ovsdb_idl_change change);
const struct ovsrec_open_vswitch *ovsrec_open_vswitch_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_open_vswitch *ovsrec_open_vswitch_track_get_next(const struct ovsrec_open_vswitch *);
#define OVSREC_OPEN_VSWITCH_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_open_vswitch_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_open_vswitch_track_get_next(ROW))

const struct ovsrec_open_vswitch *ovsrec_open_vswitch_table_track_get_first(const struct ovsrec_open_vswitch_table *);
#define OVSREC_OPEN_VSWITCH_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_open_vswitch_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_open_vswitch_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_open_vswitch_is_new(const struct ovsrec_open_vswitch *row)
{
    return ovsrec_open_vswitch_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_open_vswitch_is_deleted(const struct ovsrec_open_vswitch *row)
{
    return ovsrec_open_vswitch_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_open_vswitch_index_destroy_row(const struct ovsrec_open_vswitch *);

struct ovsrec_open_vswitch *ovsrec_open_vswitch_index_find(struct ovsdb_idl_index *, const struct ovsrec_open_vswitch *);

int ovsrec_open_vswitch_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_open_vswitch *, 
    const struct ovsrec_open_vswitch *);
struct ovsdb_idl_cursor ovsrec_open_vswitch_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_open_vswitch_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_open_vswitch *);
struct ovsdb_idl_cursor ovsrec_open_vswitch_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_open_vswitch *);

struct ovsrec_open_vswitch *ovsrec_open_vswitch_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_OPEN_VSWITCH_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_open_vswitch_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_open_vswitch_cursor_data(&cursor__), \
                  !(TO) || ovsrec_open_vswitch_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_OPEN_VSWITCH_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_open_vswitch_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_open_vswitch_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_OPEN_VSWITCH_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_open_vswitch_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_open_vswitch_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_open_vswitch_init(struct ovsrec_open_vswitch *);
void ovsrec_open_vswitch_delete(const struct ovsrec_open_vswitch *);
struct ovsrec_open_vswitch *ovsrec_open_vswitch_insert(struct ovsdb_idl_txn *);
struct ovsrec_open_vswitch *ovsrec_open_vswitch_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_open_vswitch_column_id' of
 * the row referenced by 'struct ovsrec_open_vswitch *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_open_vswitch_is_updated(const struct ovsrec_open_vswitch *, enum ovsrec_open_vswitch_column_id);

void ovsrec_open_vswitch_verify_bridges(const struct ovsrec_open_vswitch *);
void ovsrec_open_vswitch_verify_cur_cfg(const struct ovsrec_open_vswitch *);
void ovsrec_open_vswitch_verify_datapath_types(const struct ovsrec_open_vswitch *);
void ovsrec_open_vswitch_verify_datapaths(const struct ovsrec_open_vswitch *);
void ovsrec_open_vswitch_verify_db_version(const struct ovsrec_open_vswitch *);
void ovsrec_open_vswitch_verify_dpdk_initialized(const struct ovsrec_open_vswitch *);
void ovsrec_open_vswitch_verify_dpdk_version(const struct ovsrec_open_vswitch *);
void ovsrec_open_vswitch_verify_external_ids(const struct ovsrec_open_vswitch *);
void ovsrec_open_vswitch_verify_iface_types(const struct ovsrec_open_vswitch *);
void ovsrec_open_vswitch_verify_manager_options(const struct ovsrec_open_vswitch *);
void ovsrec_open_vswitch_verify_next_cfg(const struct ovsrec_open_vswitch *);
void ovsrec_open_vswitch_verify_other_config(const struct ovsrec_open_vswitch *);
void ovsrec_open_vswitch_verify_ovs_version(const struct ovsrec_open_vswitch *);
void ovsrec_open_vswitch_verify_ssl(const struct ovsrec_open_vswitch *);
void ovsrec_open_vswitch_verify_statistics(const struct ovsrec_open_vswitch *);
void ovsrec_open_vswitch_verify_system_type(const struct ovsrec_open_vswitch *);
void ovsrec_open_vswitch_verify_system_version(const struct ovsrec_open_vswitch *);

const struct ovsdb_datum *ovsrec_open_vswitch_get_bridges(const struct ovsrec_open_vswitch *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_open_vswitch_get_cur_cfg(const struct ovsrec_open_vswitch *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_open_vswitch_get_datapath_types(const struct ovsrec_open_vswitch *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_open_vswitch_get_datapaths(const struct ovsrec_open_vswitch *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_open_vswitch_get_db_version(const struct ovsrec_open_vswitch *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_open_vswitch_get_dpdk_initialized(const struct ovsrec_open_vswitch *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_open_vswitch_get_dpdk_version(const struct ovsrec_open_vswitch *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_open_vswitch_get_external_ids(const struct ovsrec_open_vswitch *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_open_vswitch_get_iface_types(const struct ovsrec_open_vswitch *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_open_vswitch_get_manager_options(const struct ovsrec_open_vswitch *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_open_vswitch_get_next_cfg(const struct ovsrec_open_vswitch *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_open_vswitch_get_other_config(const struct ovsrec_open_vswitch *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_open_vswitch_get_ovs_version(const struct ovsrec_open_vswitch *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_open_vswitch_get_ssl(const struct ovsrec_open_vswitch *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_open_vswitch_get_statistics(const struct ovsrec_open_vswitch *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_open_vswitch_get_system_type(const struct ovsrec_open_vswitch *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_open_vswitch_get_system_version(const struct ovsrec_open_vswitch *, enum ovsdb_atomic_type key_type);

void ovsrec_open_vswitch_set_bridges(const struct ovsrec_open_vswitch *, struct ovsrec_bridge **bridges, size_t n_bridges);
void ovsrec_open_vswitch_set_cur_cfg(const struct ovsrec_open_vswitch *, int64_t cur_cfg);
void ovsrec_open_vswitch_set_datapath_types(const struct ovsrec_open_vswitch *, const char **datapath_types, size_t n_datapath_types);
void ovsrec_open_vswitch_set_datapaths(const struct ovsrec_open_vswitch *, const char **key_datapaths, struct ovsrec_datapath **value_datapaths, size_t n_datapaths);
void ovsrec_open_vswitch_set_db_version(const struct ovsrec_open_vswitch *, const char *db_version);
void ovsrec_open_vswitch_set_dpdk_initialized(const struct ovsrec_open_vswitch *, bool dpdk_initialized);
void ovsrec_open_vswitch_set_dpdk_version(const struct ovsrec_open_vswitch *, const char *dpdk_version);
void ovsrec_open_vswitch_set_external_ids(const struct ovsrec_open_vswitch *, const struct smap *);
void ovsrec_open_vswitch_set_iface_types(const struct ovsrec_open_vswitch *, const char **iface_types, size_t n_iface_types);
void ovsrec_open_vswitch_set_manager_options(const struct ovsrec_open_vswitch *, struct ovsrec_manager **manager_options, size_t n_manager_options);
void ovsrec_open_vswitch_set_next_cfg(const struct ovsrec_open_vswitch *, int64_t next_cfg);
void ovsrec_open_vswitch_set_other_config(const struct ovsrec_open_vswitch *, const struct smap *);
void ovsrec_open_vswitch_set_ovs_version(const struct ovsrec_open_vswitch *, const char *ovs_version);
void ovsrec_open_vswitch_set_ssl(const struct ovsrec_open_vswitch *, const struct ovsrec_ssl *ssl);
void ovsrec_open_vswitch_set_statistics(const struct ovsrec_open_vswitch *, const struct smap *);
void ovsrec_open_vswitch_set_system_type(const struct ovsrec_open_vswitch *, const char *system_type);
void ovsrec_open_vswitch_set_system_version(const struct ovsrec_open_vswitch *, const char *system_version);

void ovsrec_open_vswitch_update_bridges_addvalue(const struct ovsrec_open_vswitch *,  const struct ovsrec_bridge *);
void ovsrec_open_vswitch_update_bridges_delvalue(const struct ovsrec_open_vswitch *,  const struct ovsrec_bridge *);
void ovsrec_open_vswitch_add_clause_bridges(struct ovsdb_idl_condition *, enum ovsdb_function function, struct uuid **bridges, size_t n_bridges);
unsigned int ovsrec_open_vswitch_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_open_vswitch_add_clause_cur_cfg(struct ovsdb_idl_condition *, enum ovsdb_function function, int64_t cur_cfg);
unsigned int ovsrec_open_vswitch_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_open_vswitch_update_datapath_types_addvalue(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_update_datapath_types_delvalue(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_add_clause_datapath_types(struct ovsdb_idl_condition *, enum ovsdb_function function, const char **datapath_types, size_t n_datapath_types);
unsigned int ovsrec_open_vswitch_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_open_vswitch_update_datapaths_setkey(const struct ovsrec_open_vswitch *,  const char *, const struct ovsrec_datapath *);
void ovsrec_open_vswitch_update_datapaths_delkey(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_add_clause_datapaths(struct ovsdb_idl_condition *, enum ovsdb_function function, const char **key_datapaths, struct uuid **value_datapaths, size_t n_datapaths);
unsigned int ovsrec_open_vswitch_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_open_vswitch_update_db_version_addvalue(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_update_db_version_delvalue(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_add_clause_db_version(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *db_version);
unsigned int ovsrec_open_vswitch_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_open_vswitch_add_clause_dpdk_initialized(struct ovsdb_idl_condition *, enum ovsdb_function function, bool dpdk_initialized);
unsigned int ovsrec_open_vswitch_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_open_vswitch_update_dpdk_version_addvalue(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_update_dpdk_version_delvalue(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_add_clause_dpdk_version(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *dpdk_version);
unsigned int ovsrec_open_vswitch_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_open_vswitch_update_external_ids_setkey(const struct ovsrec_open_vswitch *,  const char *, const char *);
void ovsrec_open_vswitch_update_external_ids_delkey(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_open_vswitch_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_open_vswitch_update_iface_types_addvalue(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_update_iface_types_delvalue(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_add_clause_iface_types(struct ovsdb_idl_condition *, enum ovsdb_function function, const char **iface_types, size_t n_iface_types);
unsigned int ovsrec_open_vswitch_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_open_vswitch_update_manager_options_addvalue(const struct ovsrec_open_vswitch *,  const struct ovsrec_manager *);
void ovsrec_open_vswitch_update_manager_options_delvalue(const struct ovsrec_open_vswitch *,  const struct ovsrec_manager *);
void ovsrec_open_vswitch_add_clause_manager_options(struct ovsdb_idl_condition *, enum ovsdb_function function, struct uuid **manager_options, size_t n_manager_options);
unsigned int ovsrec_open_vswitch_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_open_vswitch_add_clause_next_cfg(struct ovsdb_idl_condition *, enum ovsdb_function function, int64_t next_cfg);
unsigned int ovsrec_open_vswitch_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_open_vswitch_update_other_config_setkey(const struct ovsrec_open_vswitch *,  const char *, const char *);
void ovsrec_open_vswitch_update_other_config_delkey(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_add_clause_other_config(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_open_vswitch_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_open_vswitch_update_ovs_version_addvalue(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_update_ovs_version_delvalue(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_add_clause_ovs_version(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *ovs_version);
unsigned int ovsrec_open_vswitch_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_open_vswitch_update_ssl_addvalue(const struct ovsrec_open_vswitch *,  const struct ovsrec_ssl *);
void ovsrec_open_vswitch_update_ssl_delvalue(const struct ovsrec_open_vswitch *,  const struct ovsrec_ssl *);
void ovsrec_open_vswitch_add_clause_ssl(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct uuid *ssl);
unsigned int ovsrec_open_vswitch_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_open_vswitch_update_statistics_setkey(const struct ovsrec_open_vswitch *,  const char *, const char *);
void ovsrec_open_vswitch_update_statistics_delkey(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_add_clause_statistics(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_open_vswitch_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_open_vswitch_update_system_type_addvalue(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_update_system_type_delvalue(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_add_clause_system_type(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *system_type);
unsigned int ovsrec_open_vswitch_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_open_vswitch_update_system_version_addvalue(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_update_system_version_delvalue(const struct ovsrec_open_vswitch *,  const char *);
void ovsrec_open_vswitch_add_clause_system_version(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *system_version);
unsigned int ovsrec_open_vswitch_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_open_vswitch *ovsrec_open_vswitch_index_init_row(struct ovsdb_idl_index *);
void ovsrec_open_vswitch_index_set_bridges(const struct ovsrec_open_vswitch *,
struct ovsrec_bridge **bridges, size_t n_bridges);
void ovsrec_open_vswitch_index_set_cur_cfg(const struct ovsrec_open_vswitch *,
int64_t cur_cfg);
void ovsrec_open_vswitch_index_set_datapath_types(const struct ovsrec_open_vswitch *,
const char **datapath_types, size_t n_datapath_types);
void ovsrec_open_vswitch_index_set_datapaths(const struct ovsrec_open_vswitch *,
const char **key_datapaths, struct ovsrec_datapath **value_datapaths, size_t n_datapaths);
void ovsrec_open_vswitch_index_set_db_version(const struct ovsrec_open_vswitch *,
const char *db_version);
void ovsrec_open_vswitch_index_set_dpdk_initialized(const struct ovsrec_open_vswitch *,
bool dpdk_initialized);
void ovsrec_open_vswitch_index_set_dpdk_version(const struct ovsrec_open_vswitch *,
const char *dpdk_version);
void ovsrec_open_vswitch_index_set_external_ids(const struct ovsrec_open_vswitch *,
const struct smap *);
void ovsrec_open_vswitch_index_set_iface_types(const struct ovsrec_open_vswitch *,
const char **iface_types, size_t n_iface_types);
void ovsrec_open_vswitch_index_set_manager_options(const struct ovsrec_open_vswitch *,
struct ovsrec_manager **manager_options, size_t n_manager_options);
void ovsrec_open_vswitch_index_set_next_cfg(const struct ovsrec_open_vswitch *,
int64_t next_cfg);
void ovsrec_open_vswitch_index_set_other_config(const struct ovsrec_open_vswitch *,
const struct smap *);
void ovsrec_open_vswitch_index_set_ovs_version(const struct ovsrec_open_vswitch *,
const char *ovs_version);
void ovsrec_open_vswitch_index_set_ssl(const struct ovsrec_open_vswitch *,
const struct ovsrec_ssl *ssl);
void ovsrec_open_vswitch_index_set_statistics(const struct ovsrec_open_vswitch *,
const struct smap *);
void ovsrec_open_vswitch_index_set_system_type(const struct ovsrec_open_vswitch *,
const char *system_type);
void ovsrec_open_vswitch_index_set_system_version(const struct ovsrec_open_vswitch *,
const char *system_version);

/* Port table. */
struct ovsrec_port {
	struct ovsdb_idl_row header_;

	/* bond_active_slave column. */
	char *bond_active_slave;

	/* bond_downdelay column. */
	int64_t bond_downdelay;

	/* bond_fake_iface column. */
	bool bond_fake_iface;

	/* bond_mode column. */
	char *bond_mode;

	/* bond_updelay column. */
	int64_t bond_updelay;

	/* cvlans column. */
	int64_t *cvlans;
	size_t n_cvlans;

	/* external_ids column. */
	struct smap external_ids;

	/* fake_bridge column. */
	bool fake_bridge;

	/* interfaces column. */
	struct ovsrec_interface **interfaces;
	size_t n_interfaces;

	/* lacp column. */
	char *lacp;

	/* mac column. */
	char *mac;

	/* name column. */
	char *name;	/* Always nonnull. */

	/* other_config column. */
	struct smap other_config;

	/* protected_ column. */
	bool protected_;

	/* qos column. */
	struct ovsrec_qos *qos;

	/* rstp_statistics column. */
	char **key_rstp_statistics;
	int64_t *value_rstp_statistics;
	size_t n_rstp_statistics;

	/* rstp_status column. */
	struct smap rstp_status;

	/* statistics column. */
	char **key_statistics;
	int64_t *value_statistics;
	size_t n_statistics;

	/* status column. */
	struct smap status;

	/* tag column. */
	int64_t *tag;
	size_t n_tag;

	/* trunks column. */
	int64_t *trunks;
	size_t n_trunks;

	/* vlan_mode column. */
	char *vlan_mode;
};

enum ovsrec_port_column_id {
    OVSREC_PORT_COL_BOND_ACTIVE_SLAVE,
    OVSREC_PORT_COL_BOND_DOWNDELAY,
    OVSREC_PORT_COL_BOND_FAKE_IFACE,
    OVSREC_PORT_COL_BOND_MODE,
    OVSREC_PORT_COL_BOND_UPDELAY,
    OVSREC_PORT_COL_CVLANS,
    OVSREC_PORT_COL_EXTERNAL_IDS,
    OVSREC_PORT_COL_FAKE_BRIDGE,
    OVSREC_PORT_COL_INTERFACES,
    OVSREC_PORT_COL_LACP,
    OVSREC_PORT_COL_MAC,
    OVSREC_PORT_COL_NAME,
    OVSREC_PORT_COL_OTHER_CONFIG,
    OVSREC_PORT_COL_PROTECTED_,
    OVSREC_PORT_COL_QOS,
    OVSREC_PORT_COL_RSTP_STATISTICS,
    OVSREC_PORT_COL_RSTP_STATUS,
    OVSREC_PORT_COL_STATISTICS,
    OVSREC_PORT_COL_STATUS,
    OVSREC_PORT_COL_TAG,
    OVSREC_PORT_COL_TRUNKS,
    OVSREC_PORT_COL_VLAN_MODE,
    OVSREC_PORT_N_COLUMNS
};

#define ovsrec_port_col_bond_active_slave (ovsrec_port_columns[OVSREC_PORT_COL_BOND_ACTIVE_SLAVE])
#define ovsrec_port_col_bond_downdelay (ovsrec_port_columns[OVSREC_PORT_COL_BOND_DOWNDELAY])
#define ovsrec_port_col_bond_fake_iface (ovsrec_port_columns[OVSREC_PORT_COL_BOND_FAKE_IFACE])
#define ovsrec_port_col_bond_mode (ovsrec_port_columns[OVSREC_PORT_COL_BOND_MODE])
#define ovsrec_port_col_bond_updelay (ovsrec_port_columns[OVSREC_PORT_COL_BOND_UPDELAY])
#define ovsrec_port_col_cvlans (ovsrec_port_columns[OVSREC_PORT_COL_CVLANS])
#define ovsrec_port_col_external_ids (ovsrec_port_columns[OVSREC_PORT_COL_EXTERNAL_IDS])
#define ovsrec_port_col_fake_bridge (ovsrec_port_columns[OVSREC_PORT_COL_FAKE_BRIDGE])
#define ovsrec_port_col_interfaces (ovsrec_port_columns[OVSREC_PORT_COL_INTERFACES])
#define ovsrec_port_col_lacp (ovsrec_port_columns[OVSREC_PORT_COL_LACP])
#define ovsrec_port_col_mac (ovsrec_port_columns[OVSREC_PORT_COL_MAC])
#define ovsrec_port_col_name (ovsrec_port_columns[OVSREC_PORT_COL_NAME])
#define ovsrec_port_col_other_config (ovsrec_port_columns[OVSREC_PORT_COL_OTHER_CONFIG])
#define ovsrec_port_col_qos (ovsrec_port_columns[OVSREC_PORT_COL_QOS])
#define ovsrec_port_col_rstp_statistics (ovsrec_port_columns[OVSREC_PORT_COL_RSTP_STATISTICS])
#define ovsrec_port_col_rstp_status (ovsrec_port_columns[OVSREC_PORT_COL_RSTP_STATUS])
#define ovsrec_port_col_statistics (ovsrec_port_columns[OVSREC_PORT_COL_STATISTICS])
#define ovsrec_port_col_status (ovsrec_port_columns[OVSREC_PORT_COL_STATUS])
#define ovsrec_port_col_tag (ovsrec_port_columns[OVSREC_PORT_COL_TAG])
#define ovsrec_port_col_trunks (ovsrec_port_columns[OVSREC_PORT_COL_TRUNKS])
#define ovsrec_port_col_vlan_mode (ovsrec_port_columns[OVSREC_PORT_COL_VLAN_MODE])
#define ovsrec_port_col_protected_ (ovsrec_port_columns[OVSREC_PORT_COL_PROTECTED_])

extern struct ovsdb_idl_column ovsrec_port_columns[OVSREC_PORT_N_COLUMNS];
bool ovsrec_server_has_port_table_col_bond_active_slave(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_bond_downdelay(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_bond_fake_iface(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_bond_mode(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_bond_updelay(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_cvlans(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_external_ids(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_fake_bridge(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_interfaces(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_lacp(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_mac(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_name(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_other_config(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_qos(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_rstp_statistics(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_rstp_status(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_statistics(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_status(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_tag(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_trunks(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_vlan_mode(const struct ovsdb_idl *); 
bool ovsrec_server_has_port_table_col_protected_(const struct ovsdb_idl *); 

bool ovsrec_server_has_port_table(const struct ovsdb_idl *);
const struct ovsrec_port_table *ovsrec_port_table_get(const struct ovsdb_idl *);
const struct ovsrec_port *ovsrec_port_table_first(const struct ovsrec_port_table *);

#define OVSREC_PORT_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_port_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_port_next(ROW))
#define OVSREC_PORT_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_port_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_port_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_PORT_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_port * ROW__next = ((ROW) = ovsrec_port_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_port_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_PORT_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_PORT_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_PORT_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_port *ovsrec_port_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_port *ovsrec_port_table_get_for_uuid(const struct ovsrec_port_table *, const struct uuid *);
const struct ovsrec_port *ovsrec_port_first(const struct ovsdb_idl *);
const struct ovsrec_port *ovsrec_port_next(const struct ovsrec_port *);
#define OVSREC_PORT_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_port_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_port_next(ROW))
#define OVSREC_PORT_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_port_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_port_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_PORT_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_port * ROW__next = ((ROW) = ovsrec_port_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_port_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_PORT_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_PORT_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_PORT_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_port_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_port_row_get_seqno(const struct ovsrec_port *row, enum ovsdb_idl_change change);
const struct ovsrec_port *ovsrec_port_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_port *ovsrec_port_track_get_next(const struct ovsrec_port *);
#define OVSREC_PORT_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_port_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_port_track_get_next(ROW))

const struct ovsrec_port *ovsrec_port_table_track_get_first(const struct ovsrec_port_table *);
#define OVSREC_PORT_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_port_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_port_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_port_is_new(const struct ovsrec_port *row)
{
    return ovsrec_port_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_port_is_deleted(const struct ovsrec_port *row)
{
    return ovsrec_port_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_port_index_destroy_row(const struct ovsrec_port *);

struct ovsrec_port *ovsrec_port_index_find(struct ovsdb_idl_index *, const struct ovsrec_port *);

int ovsrec_port_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_port *, 
    const struct ovsrec_port *);
struct ovsdb_idl_cursor ovsrec_port_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_port_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_port *);
struct ovsdb_idl_cursor ovsrec_port_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_port *);

struct ovsrec_port *ovsrec_port_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_PORT_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_port_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_port_cursor_data(&cursor__), \
                  !(TO) || ovsrec_port_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_PORT_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_port_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_port_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_PORT_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_port_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_port_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_port_init(struct ovsrec_port *);
void ovsrec_port_delete(const struct ovsrec_port *);
struct ovsrec_port *ovsrec_port_insert(struct ovsdb_idl_txn *);
struct ovsrec_port *ovsrec_port_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_port_column_id' of
 * the row referenced by 'struct ovsrec_port *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_port_is_updated(const struct ovsrec_port *, enum ovsrec_port_column_id);

void ovsrec_port_verify_bond_active_slave(const struct ovsrec_port *);
void ovsrec_port_verify_bond_downdelay(const struct ovsrec_port *);
void ovsrec_port_verify_bond_fake_iface(const struct ovsrec_port *);
void ovsrec_port_verify_bond_mode(const struct ovsrec_port *);
void ovsrec_port_verify_bond_updelay(const struct ovsrec_port *);
void ovsrec_port_verify_cvlans(const struct ovsrec_port *);
void ovsrec_port_verify_external_ids(const struct ovsrec_port *);
void ovsrec_port_verify_fake_bridge(const struct ovsrec_port *);
void ovsrec_port_verify_interfaces(const struct ovsrec_port *);
void ovsrec_port_verify_lacp(const struct ovsrec_port *);
void ovsrec_port_verify_mac(const struct ovsrec_port *);
void ovsrec_port_verify_name(const struct ovsrec_port *);
void ovsrec_port_verify_other_config(const struct ovsrec_port *);
void ovsrec_port_verify_protected_(const struct ovsrec_port *);
void ovsrec_port_verify_qos(const struct ovsrec_port *);
void ovsrec_port_verify_rstp_statistics(const struct ovsrec_port *);
void ovsrec_port_verify_rstp_status(const struct ovsrec_port *);
void ovsrec_port_verify_statistics(const struct ovsrec_port *);
void ovsrec_port_verify_status(const struct ovsrec_port *);
void ovsrec_port_verify_tag(const struct ovsrec_port *);
void ovsrec_port_verify_trunks(const struct ovsrec_port *);
void ovsrec_port_verify_vlan_mode(const struct ovsrec_port *);

const struct ovsdb_datum *ovsrec_port_get_bond_active_slave(const struct ovsrec_port *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_port_get_bond_downdelay(const struct ovsrec_port *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_port_get_bond_fake_iface(const struct ovsrec_port *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_port_get_bond_mode(const struct ovsrec_port *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_port_get_bond_updelay(const struct ovsrec_port *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_port_get_cvlans(const struct ovsrec_port *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_port_get_external_ids(const struct ovsrec_port *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_port_get_fake_bridge(const struct ovsrec_port *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_port_get_interfaces(const struct ovsrec_port *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_port_get_lacp(const struct ovsrec_port *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_port_get_mac(const struct ovsrec_port *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_port_get_name(const struct ovsrec_port *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_port_get_other_config(const struct ovsrec_port *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_port_get_protected_(const struct ovsrec_port *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_port_get_qos(const struct ovsrec_port *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_port_get_rstp_statistics(const struct ovsrec_port *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_port_get_rstp_status(const struct ovsrec_port *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_port_get_statistics(const struct ovsrec_port *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_port_get_status(const struct ovsrec_port *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_port_get_tag(const struct ovsrec_port *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_port_get_trunks(const struct ovsrec_port *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_port_get_vlan_mode(const struct ovsrec_port *, enum ovsdb_atomic_type key_type);

void ovsrec_port_set_bond_active_slave(const struct ovsrec_port *, const char *bond_active_slave);
void ovsrec_port_set_bond_downdelay(const struct ovsrec_port *, int64_t bond_downdelay);
void ovsrec_port_set_bond_fake_iface(const struct ovsrec_port *, bool bond_fake_iface);
void ovsrec_port_set_bond_mode(const struct ovsrec_port *, const char *bond_mode);
void ovsrec_port_set_bond_updelay(const struct ovsrec_port *, int64_t bond_updelay);
void ovsrec_port_set_cvlans(const struct ovsrec_port *, const int64_t *cvlans, size_t n_cvlans);
void ovsrec_port_set_external_ids(const struct ovsrec_port *, const struct smap *);
void ovsrec_port_set_fake_bridge(const struct ovsrec_port *, bool fake_bridge);
void ovsrec_port_set_interfaces(const struct ovsrec_port *, struct ovsrec_interface **interfaces, size_t n_interfaces);
void ovsrec_port_set_lacp(const struct ovsrec_port *, const char *lacp);
void ovsrec_port_set_mac(const struct ovsrec_port *, const char *mac);
void ovsrec_port_set_name(const struct ovsrec_port *, const char *name);
void ovsrec_port_set_other_config(const struct ovsrec_port *, const struct smap *);
void ovsrec_port_set_protected_(const struct ovsrec_port *, bool protected_);
void ovsrec_port_set_qos(const struct ovsrec_port *, const struct ovsrec_qos *qos);
void ovsrec_port_set_rstp_statistics(const struct ovsrec_port *, const char **key_rstp_statistics, const int64_t *value_rstp_statistics, size_t n_rstp_statistics);
void ovsrec_port_set_rstp_status(const struct ovsrec_port *, const struct smap *);
void ovsrec_port_set_statistics(const struct ovsrec_port *, const char **key_statistics, const int64_t *value_statistics, size_t n_statistics);
void ovsrec_port_set_status(const struct ovsrec_port *, const struct smap *);
void ovsrec_port_set_tag(const struct ovsrec_port *, const int64_t *tag, size_t n_tag);
void ovsrec_port_set_trunks(const struct ovsrec_port *, const int64_t *trunks, size_t n_trunks);
void ovsrec_port_set_vlan_mode(const struct ovsrec_port *, const char *vlan_mode);

void ovsrec_port_update_bond_active_slave_addvalue(const struct ovsrec_port *,  const char *);
void ovsrec_port_update_bond_active_slave_delvalue(const struct ovsrec_port *,  const char *);
void ovsrec_port_add_clause_bond_active_slave(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *bond_active_slave);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_add_clause_bond_downdelay(struct ovsdb_idl_condition *, enum ovsdb_function function, int64_t bond_downdelay);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_add_clause_bond_fake_iface(struct ovsdb_idl_condition *, enum ovsdb_function function, bool bond_fake_iface);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_update_bond_mode_addvalue(const struct ovsrec_port *,  const char *);
void ovsrec_port_update_bond_mode_delvalue(const struct ovsrec_port *,  const char *);
void ovsrec_port_add_clause_bond_mode(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *bond_mode);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_add_clause_bond_updelay(struct ovsdb_idl_condition *, enum ovsdb_function function, int64_t bond_updelay);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_update_cvlans_addvalue(const struct ovsrec_port *,  int64_t );
void ovsrec_port_update_cvlans_delvalue(const struct ovsrec_port *,  int64_t );
void ovsrec_port_add_clause_cvlans(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *cvlans, size_t n_cvlans);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_update_external_ids_setkey(const struct ovsrec_port *,  const char *, const char *);
void ovsrec_port_update_external_ids_delkey(const struct ovsrec_port *,  const char *);
void ovsrec_port_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_add_clause_fake_bridge(struct ovsdb_idl_condition *, enum ovsdb_function function, bool fake_bridge);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_update_interfaces_addvalue(const struct ovsrec_port *,  const struct ovsrec_interface *);
void ovsrec_port_update_interfaces_delvalue(const struct ovsrec_port *,  const struct ovsrec_interface *);
void ovsrec_port_add_clause_interfaces(struct ovsdb_idl_condition *, enum ovsdb_function function, struct uuid **interfaces, size_t n_interfaces);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_update_lacp_addvalue(const struct ovsrec_port *,  const char *);
void ovsrec_port_update_lacp_delvalue(const struct ovsrec_port *,  const char *);
void ovsrec_port_add_clause_lacp(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *lacp);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_update_mac_addvalue(const struct ovsrec_port *,  const char *);
void ovsrec_port_update_mac_delvalue(const struct ovsrec_port *,  const char *);
void ovsrec_port_add_clause_mac(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *mac);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_add_clause_name(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *name);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_update_other_config_setkey(const struct ovsrec_port *,  const char *, const char *);
void ovsrec_port_update_other_config_delkey(const struct ovsrec_port *,  const char *);
void ovsrec_port_add_clause_other_config(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_add_clause_protected_(struct ovsdb_idl_condition *, enum ovsdb_function function, bool protected_);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_update_qos_addvalue(const struct ovsrec_port *,  const struct ovsrec_qos *);
void ovsrec_port_update_qos_delvalue(const struct ovsrec_port *,  const struct ovsrec_qos *);
void ovsrec_port_add_clause_qos(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct uuid *qos);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_update_rstp_statistics_setkey(const struct ovsrec_port *,  const char *, int64_t );
void ovsrec_port_update_rstp_statistics_delkey(const struct ovsrec_port *,  const char *);
void ovsrec_port_add_clause_rstp_statistics(struct ovsdb_idl_condition *, enum ovsdb_function function, const char **key_rstp_statistics, const int64_t *value_rstp_statistics, size_t n_rstp_statistics);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_update_rstp_status_setkey(const struct ovsrec_port *,  const char *, const char *);
void ovsrec_port_update_rstp_status_delkey(const struct ovsrec_port *,  const char *);
void ovsrec_port_add_clause_rstp_status(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_update_statistics_setkey(const struct ovsrec_port *,  const char *, int64_t );
void ovsrec_port_update_statistics_delkey(const struct ovsrec_port *,  const char *);
void ovsrec_port_add_clause_statistics(struct ovsdb_idl_condition *, enum ovsdb_function function, const char **key_statistics, const int64_t *value_statistics, size_t n_statistics);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_update_status_setkey(const struct ovsrec_port *,  const char *, const char *);
void ovsrec_port_update_status_delkey(const struct ovsrec_port *,  const char *);
void ovsrec_port_add_clause_status(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_update_tag_addvalue(const struct ovsrec_port *,  int64_t );
void ovsrec_port_update_tag_delvalue(const struct ovsrec_port *,  int64_t );
void ovsrec_port_add_clause_tag(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *tag, size_t n_tag);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_update_trunks_addvalue(const struct ovsrec_port *,  int64_t );
void ovsrec_port_update_trunks_delvalue(const struct ovsrec_port *,  int64_t );
void ovsrec_port_add_clause_trunks(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *trunks, size_t n_trunks);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_port_update_vlan_mode_addvalue(const struct ovsrec_port *,  const char *);
void ovsrec_port_update_vlan_mode_delvalue(const struct ovsrec_port *,  const char *);
void ovsrec_port_add_clause_vlan_mode(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *vlan_mode);
unsigned int ovsrec_port_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_port *ovsrec_port_index_init_row(struct ovsdb_idl_index *);
void ovsrec_port_index_set_bond_active_slave(const struct ovsrec_port *,
const char *bond_active_slave);
void ovsrec_port_index_set_bond_downdelay(const struct ovsrec_port *,
int64_t bond_downdelay);
void ovsrec_port_index_set_bond_fake_iface(const struct ovsrec_port *,
bool bond_fake_iface);
void ovsrec_port_index_set_bond_mode(const struct ovsrec_port *,
const char *bond_mode);
void ovsrec_port_index_set_bond_updelay(const struct ovsrec_port *,
int64_t bond_updelay);
void ovsrec_port_index_set_cvlans(const struct ovsrec_port *,
const int64_t *cvlans, size_t n_cvlans);
void ovsrec_port_index_set_external_ids(const struct ovsrec_port *,
const struct smap *);
void ovsrec_port_index_set_fake_bridge(const struct ovsrec_port *,
bool fake_bridge);
void ovsrec_port_index_set_interfaces(const struct ovsrec_port *,
struct ovsrec_interface **interfaces, size_t n_interfaces);
void ovsrec_port_index_set_lacp(const struct ovsrec_port *,
const char *lacp);
void ovsrec_port_index_set_mac(const struct ovsrec_port *,
const char *mac);
void ovsrec_port_index_set_name(const struct ovsrec_port *,
const char *name);
void ovsrec_port_index_set_other_config(const struct ovsrec_port *,
const struct smap *);
void ovsrec_port_index_set_protected_(const struct ovsrec_port *,
bool protected_);
void ovsrec_port_index_set_qos(const struct ovsrec_port *,
const struct ovsrec_qos *qos);
void ovsrec_port_index_set_rstp_statistics(const struct ovsrec_port *,
const char **key_rstp_statistics, const int64_t *value_rstp_statistics, size_t n_rstp_statistics);
void ovsrec_port_index_set_rstp_status(const struct ovsrec_port *,
const struct smap *);
void ovsrec_port_index_set_statistics(const struct ovsrec_port *,
const char **key_statistics, const int64_t *value_statistics, size_t n_statistics);
void ovsrec_port_index_set_status(const struct ovsrec_port *,
const struct smap *);
void ovsrec_port_index_set_tag(const struct ovsrec_port *,
const int64_t *tag, size_t n_tag);
void ovsrec_port_index_set_trunks(const struct ovsrec_port *,
const int64_t *trunks, size_t n_trunks);
void ovsrec_port_index_set_vlan_mode(const struct ovsrec_port *,
const char *vlan_mode);

/* QoS table. */
struct ovsrec_qos {
	struct ovsdb_idl_row header_;

	/* external_ids column. */
	struct smap external_ids;

	/* other_config column. */
	struct smap other_config;

	/* queues column. */
	int64_t *key_queues;
	struct ovsrec_queue **value_queues;
	size_t n_queues;

	/* type column. */
	char *type;	/* Always nonnull. */
};

enum ovsrec_qos_column_id {
    OVSREC_QOS_COL_EXTERNAL_IDS,
    OVSREC_QOS_COL_OTHER_CONFIG,
    OVSREC_QOS_COL_QUEUES,
    OVSREC_QOS_COL_TYPE,
    OVSREC_QOS_N_COLUMNS
};

#define ovsrec_qos_col_external_ids (ovsrec_qos_columns[OVSREC_QOS_COL_EXTERNAL_IDS])
#define ovsrec_qos_col_other_config (ovsrec_qos_columns[OVSREC_QOS_COL_OTHER_CONFIG])
#define ovsrec_qos_col_queues (ovsrec_qos_columns[OVSREC_QOS_COL_QUEUES])
#define ovsrec_qos_col_type (ovsrec_qos_columns[OVSREC_QOS_COL_TYPE])

extern struct ovsdb_idl_column ovsrec_qos_columns[OVSREC_QOS_N_COLUMNS];
bool ovsrec_server_has_qos_table_col_external_ids(const struct ovsdb_idl *); 
bool ovsrec_server_has_qos_table_col_other_config(const struct ovsdb_idl *); 
bool ovsrec_server_has_qos_table_col_queues(const struct ovsdb_idl *); 
bool ovsrec_server_has_qos_table_col_type(const struct ovsdb_idl *); 

bool ovsrec_server_has_qos_table(const struct ovsdb_idl *);
const struct ovsrec_qos_table *ovsrec_qos_table_get(const struct ovsdb_idl *);
const struct ovsrec_qos *ovsrec_qos_table_first(const struct ovsrec_qos_table *);

#define OVSREC_QOS_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_qos_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_qos_next(ROW))
#define OVSREC_QOS_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_qos_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_qos_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_QOS_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_qos * ROW__next = ((ROW) = ovsrec_qos_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_qos_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_QOS_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_QOS_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_QOS_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_qos *ovsrec_qos_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_qos *ovsrec_qos_table_get_for_uuid(const struct ovsrec_qos_table *, const struct uuid *);
const struct ovsrec_qos *ovsrec_qos_first(const struct ovsdb_idl *);
const struct ovsrec_qos *ovsrec_qos_next(const struct ovsrec_qos *);
#define OVSREC_QOS_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_qos_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_qos_next(ROW))
#define OVSREC_QOS_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_qos_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_qos_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_QOS_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_qos * ROW__next = ((ROW) = ovsrec_qos_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_qos_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_QOS_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_QOS_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_QOS_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_qos_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_qos_row_get_seqno(const struct ovsrec_qos *row, enum ovsdb_idl_change change);
const struct ovsrec_qos *ovsrec_qos_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_qos *ovsrec_qos_track_get_next(const struct ovsrec_qos *);
#define OVSREC_QOS_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_qos_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_qos_track_get_next(ROW))

const struct ovsrec_qos *ovsrec_qos_table_track_get_first(const struct ovsrec_qos_table *);
#define OVSREC_QOS_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_qos_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_qos_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_qos_is_new(const struct ovsrec_qos *row)
{
    return ovsrec_qos_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_qos_is_deleted(const struct ovsrec_qos *row)
{
    return ovsrec_qos_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_qos_index_destroy_row(const struct ovsrec_qos *);

struct ovsrec_qos *ovsrec_qos_index_find(struct ovsdb_idl_index *, const struct ovsrec_qos *);

int ovsrec_qos_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_qos *, 
    const struct ovsrec_qos *);
struct ovsdb_idl_cursor ovsrec_qos_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_qos_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_qos *);
struct ovsdb_idl_cursor ovsrec_qos_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_qos *);

struct ovsrec_qos *ovsrec_qos_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_QOS_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_qos_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_qos_cursor_data(&cursor__), \
                  !(TO) || ovsrec_qos_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_QOS_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_qos_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_qos_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_QOS_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_qos_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_qos_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_qos_init(struct ovsrec_qos *);
void ovsrec_qos_delete(const struct ovsrec_qos *);
struct ovsrec_qos *ovsrec_qos_insert(struct ovsdb_idl_txn *);
struct ovsrec_qos *ovsrec_qos_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_qos_column_id' of
 * the row referenced by 'struct ovsrec_qos *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_qos_is_updated(const struct ovsrec_qos *, enum ovsrec_qos_column_id);

void ovsrec_qos_verify_external_ids(const struct ovsrec_qos *);
void ovsrec_qos_verify_other_config(const struct ovsrec_qos *);
void ovsrec_qos_verify_queues(const struct ovsrec_qos *);
void ovsrec_qos_verify_type(const struct ovsrec_qos *);

const struct ovsdb_datum *ovsrec_qos_get_external_ids(const struct ovsrec_qos *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_qos_get_other_config(const struct ovsrec_qos *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_qos_get_queues(const struct ovsrec_qos *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_qos_get_type(const struct ovsrec_qos *, enum ovsdb_atomic_type key_type);

void ovsrec_qos_set_external_ids(const struct ovsrec_qos *, const struct smap *);
void ovsrec_qos_set_other_config(const struct ovsrec_qos *, const struct smap *);
void ovsrec_qos_set_queues(const struct ovsrec_qos *, const int64_t *key_queues, struct ovsrec_queue **value_queues, size_t n_queues);
void ovsrec_qos_set_type(const struct ovsrec_qos *, const char *type);

void ovsrec_qos_update_external_ids_setkey(const struct ovsrec_qos *,  const char *, const char *);
void ovsrec_qos_update_external_ids_delkey(const struct ovsrec_qos *,  const char *);
void ovsrec_qos_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_qos_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_qos_update_other_config_setkey(const struct ovsrec_qos *,  const char *, const char *);
void ovsrec_qos_update_other_config_delkey(const struct ovsrec_qos *,  const char *);
void ovsrec_qos_add_clause_other_config(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_qos_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_qos_update_queues_setkey(const struct ovsrec_qos *,  int64_t , const struct ovsrec_queue *);
void ovsrec_qos_update_queues_delkey(const struct ovsrec_qos *,  int64_t );
void ovsrec_qos_add_clause_queues(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *key_queues, struct uuid **value_queues, size_t n_queues);
unsigned int ovsrec_qos_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_qos_add_clause_type(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *type);
unsigned int ovsrec_qos_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_qos *ovsrec_qos_index_init_row(struct ovsdb_idl_index *);
void ovsrec_qos_index_set_external_ids(const struct ovsrec_qos *,
const struct smap *);
void ovsrec_qos_index_set_other_config(const struct ovsrec_qos *,
const struct smap *);
void ovsrec_qos_index_set_queues(const struct ovsrec_qos *,
const int64_t *key_queues, struct ovsrec_queue **value_queues, size_t n_queues);
void ovsrec_qos_index_set_type(const struct ovsrec_qos *,
const char *type);

/* Queue table. */
struct ovsrec_queue {
	struct ovsdb_idl_row header_;

	/* dscp column. */
	int64_t *dscp;
	size_t n_dscp;

	/* external_ids column. */
	struct smap external_ids;

	/* other_config column. */
	struct smap other_config;
};

enum ovsrec_queue_column_id {
    OVSREC_QUEUE_COL_DSCP,
    OVSREC_QUEUE_COL_EXTERNAL_IDS,
    OVSREC_QUEUE_COL_OTHER_CONFIG,
    OVSREC_QUEUE_N_COLUMNS
};

#define ovsrec_queue_col_dscp (ovsrec_queue_columns[OVSREC_QUEUE_COL_DSCP])
#define ovsrec_queue_col_external_ids (ovsrec_queue_columns[OVSREC_QUEUE_COL_EXTERNAL_IDS])
#define ovsrec_queue_col_other_config (ovsrec_queue_columns[OVSREC_QUEUE_COL_OTHER_CONFIG])

extern struct ovsdb_idl_column ovsrec_queue_columns[OVSREC_QUEUE_N_COLUMNS];
bool ovsrec_server_has_queue_table_col_dscp(const struct ovsdb_idl *); 
bool ovsrec_server_has_queue_table_col_external_ids(const struct ovsdb_idl *); 
bool ovsrec_server_has_queue_table_col_other_config(const struct ovsdb_idl *); 

bool ovsrec_server_has_queue_table(const struct ovsdb_idl *);
const struct ovsrec_queue_table *ovsrec_queue_table_get(const struct ovsdb_idl *);
const struct ovsrec_queue *ovsrec_queue_table_first(const struct ovsrec_queue_table *);

#define OVSREC_QUEUE_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_queue_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_queue_next(ROW))
#define OVSREC_QUEUE_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_queue_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_queue_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_QUEUE_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_queue * ROW__next = ((ROW) = ovsrec_queue_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_queue_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_QUEUE_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_QUEUE_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_QUEUE_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_queue *ovsrec_queue_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_queue *ovsrec_queue_table_get_for_uuid(const struct ovsrec_queue_table *, const struct uuid *);
const struct ovsrec_queue *ovsrec_queue_first(const struct ovsdb_idl *);
const struct ovsrec_queue *ovsrec_queue_next(const struct ovsrec_queue *);
#define OVSREC_QUEUE_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_queue_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_queue_next(ROW))
#define OVSREC_QUEUE_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_queue_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_queue_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_QUEUE_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_queue * ROW__next = ((ROW) = ovsrec_queue_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_queue_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_QUEUE_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_QUEUE_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_QUEUE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_queue_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_queue_row_get_seqno(const struct ovsrec_queue *row, enum ovsdb_idl_change change);
const struct ovsrec_queue *ovsrec_queue_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_queue *ovsrec_queue_track_get_next(const struct ovsrec_queue *);
#define OVSREC_QUEUE_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_queue_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_queue_track_get_next(ROW))

const struct ovsrec_queue *ovsrec_queue_table_track_get_first(const struct ovsrec_queue_table *);
#define OVSREC_QUEUE_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_queue_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_queue_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_queue_is_new(const struct ovsrec_queue *row)
{
    return ovsrec_queue_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_queue_is_deleted(const struct ovsrec_queue *row)
{
    return ovsrec_queue_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_queue_index_destroy_row(const struct ovsrec_queue *);

struct ovsrec_queue *ovsrec_queue_index_find(struct ovsdb_idl_index *, const struct ovsrec_queue *);

int ovsrec_queue_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_queue *, 
    const struct ovsrec_queue *);
struct ovsdb_idl_cursor ovsrec_queue_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_queue_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_queue *);
struct ovsdb_idl_cursor ovsrec_queue_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_queue *);

struct ovsrec_queue *ovsrec_queue_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_QUEUE_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_queue_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_queue_cursor_data(&cursor__), \
                  !(TO) || ovsrec_queue_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_QUEUE_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_queue_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_queue_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_QUEUE_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_queue_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_queue_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_queue_init(struct ovsrec_queue *);
void ovsrec_queue_delete(const struct ovsrec_queue *);
struct ovsrec_queue *ovsrec_queue_insert(struct ovsdb_idl_txn *);
struct ovsrec_queue *ovsrec_queue_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_queue_column_id' of
 * the row referenced by 'struct ovsrec_queue *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_queue_is_updated(const struct ovsrec_queue *, enum ovsrec_queue_column_id);

void ovsrec_queue_verify_dscp(const struct ovsrec_queue *);
void ovsrec_queue_verify_external_ids(const struct ovsrec_queue *);
void ovsrec_queue_verify_other_config(const struct ovsrec_queue *);

const struct ovsdb_datum *ovsrec_queue_get_dscp(const struct ovsrec_queue *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_queue_get_external_ids(const struct ovsrec_queue *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_queue_get_other_config(const struct ovsrec_queue *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);

void ovsrec_queue_set_dscp(const struct ovsrec_queue *, const int64_t *dscp, size_t n_dscp);
void ovsrec_queue_set_external_ids(const struct ovsrec_queue *, const struct smap *);
void ovsrec_queue_set_other_config(const struct ovsrec_queue *, const struct smap *);

void ovsrec_queue_update_dscp_addvalue(const struct ovsrec_queue *,  int64_t );
void ovsrec_queue_update_dscp_delvalue(const struct ovsrec_queue *,  int64_t );
void ovsrec_queue_add_clause_dscp(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *dscp, size_t n_dscp);
unsigned int ovsrec_queue_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_queue_update_external_ids_setkey(const struct ovsrec_queue *,  const char *, const char *);
void ovsrec_queue_update_external_ids_delkey(const struct ovsrec_queue *,  const char *);
void ovsrec_queue_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_queue_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_queue_update_other_config_setkey(const struct ovsrec_queue *,  const char *, const char *);
void ovsrec_queue_update_other_config_delkey(const struct ovsrec_queue *,  const char *);
void ovsrec_queue_add_clause_other_config(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_queue_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_queue *ovsrec_queue_index_init_row(struct ovsdb_idl_index *);
void ovsrec_queue_index_set_dscp(const struct ovsrec_queue *,
const int64_t *dscp, size_t n_dscp);
void ovsrec_queue_index_set_external_ids(const struct ovsrec_queue *,
const struct smap *);
void ovsrec_queue_index_set_other_config(const struct ovsrec_queue *,
const struct smap *);

/* SSL table. */
struct ovsrec_ssl {
	struct ovsdb_idl_row header_;

	/* bootstrap_ca_cert column. */
	bool bootstrap_ca_cert;

	/* ca_cert column. */
	char *ca_cert;	/* Always nonnull. */

	/* certificate column. */
	char *certificate;	/* Always nonnull. */

	/* external_ids column. */
	struct smap external_ids;

	/* private_key column. */
	char *private_key;	/* Always nonnull. */
};

enum ovsrec_ssl_column_id {
    OVSREC_SSL_COL_BOOTSTRAP_CA_CERT,
    OVSREC_SSL_COL_CA_CERT,
    OVSREC_SSL_COL_CERTIFICATE,
    OVSREC_SSL_COL_EXTERNAL_IDS,
    OVSREC_SSL_COL_PRIVATE_KEY,
    OVSREC_SSL_N_COLUMNS
};

#define ovsrec_ssl_col_bootstrap_ca_cert (ovsrec_ssl_columns[OVSREC_SSL_COL_BOOTSTRAP_CA_CERT])
#define ovsrec_ssl_col_ca_cert (ovsrec_ssl_columns[OVSREC_SSL_COL_CA_CERT])
#define ovsrec_ssl_col_certificate (ovsrec_ssl_columns[OVSREC_SSL_COL_CERTIFICATE])
#define ovsrec_ssl_col_external_ids (ovsrec_ssl_columns[OVSREC_SSL_COL_EXTERNAL_IDS])
#define ovsrec_ssl_col_private_key (ovsrec_ssl_columns[OVSREC_SSL_COL_PRIVATE_KEY])

extern struct ovsdb_idl_column ovsrec_ssl_columns[OVSREC_SSL_N_COLUMNS];
bool ovsrec_server_has_ssl_table_col_bootstrap_ca_cert(const struct ovsdb_idl *); 
bool ovsrec_server_has_ssl_table_col_ca_cert(const struct ovsdb_idl *); 
bool ovsrec_server_has_ssl_table_col_certificate(const struct ovsdb_idl *); 
bool ovsrec_server_has_ssl_table_col_external_ids(const struct ovsdb_idl *); 
bool ovsrec_server_has_ssl_table_col_private_key(const struct ovsdb_idl *); 

bool ovsrec_server_has_ssl_table(const struct ovsdb_idl *);
const struct ovsrec_ssl_table *ovsrec_ssl_table_get(const struct ovsdb_idl *);
const struct ovsrec_ssl *ovsrec_ssl_table_first(const struct ovsrec_ssl_table *);

#define OVSREC_SSL_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_ssl_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_ssl_next(ROW))
#define OVSREC_SSL_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_ssl_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_ssl_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_SSL_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_ssl * ROW__next = ((ROW) = ovsrec_ssl_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_ssl_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_SSL_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_SSL_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_SSL_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_ssl *ovsrec_ssl_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_ssl *ovsrec_ssl_table_get_for_uuid(const struct ovsrec_ssl_table *, const struct uuid *);
const struct ovsrec_ssl *ovsrec_ssl_first(const struct ovsdb_idl *);
const struct ovsrec_ssl *ovsrec_ssl_next(const struct ovsrec_ssl *);
#define OVSREC_SSL_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_ssl_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_ssl_next(ROW))
#define OVSREC_SSL_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_ssl_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_ssl_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_SSL_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_ssl * ROW__next = ((ROW) = ovsrec_ssl_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_ssl_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_SSL_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_SSL_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_SSL_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_ssl_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_ssl_row_get_seqno(const struct ovsrec_ssl *row, enum ovsdb_idl_change change);
const struct ovsrec_ssl *ovsrec_ssl_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_ssl *ovsrec_ssl_track_get_next(const struct ovsrec_ssl *);
#define OVSREC_SSL_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_ssl_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_ssl_track_get_next(ROW))

const struct ovsrec_ssl *ovsrec_ssl_table_track_get_first(const struct ovsrec_ssl_table *);
#define OVSREC_SSL_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_ssl_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_ssl_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_ssl_is_new(const struct ovsrec_ssl *row)
{
    return ovsrec_ssl_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_ssl_is_deleted(const struct ovsrec_ssl *row)
{
    return ovsrec_ssl_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_ssl_index_destroy_row(const struct ovsrec_ssl *);

struct ovsrec_ssl *ovsrec_ssl_index_find(struct ovsdb_idl_index *, const struct ovsrec_ssl *);

int ovsrec_ssl_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_ssl *, 
    const struct ovsrec_ssl *);
struct ovsdb_idl_cursor ovsrec_ssl_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_ssl_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_ssl *);
struct ovsdb_idl_cursor ovsrec_ssl_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_ssl *);

struct ovsrec_ssl *ovsrec_ssl_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_SSL_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_ssl_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_ssl_cursor_data(&cursor__), \
                  !(TO) || ovsrec_ssl_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_SSL_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_ssl_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_ssl_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_SSL_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_ssl_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_ssl_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_ssl_init(struct ovsrec_ssl *);
void ovsrec_ssl_delete(const struct ovsrec_ssl *);
struct ovsrec_ssl *ovsrec_ssl_insert(struct ovsdb_idl_txn *);
struct ovsrec_ssl *ovsrec_ssl_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_ssl_column_id' of
 * the row referenced by 'struct ovsrec_ssl *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_ssl_is_updated(const struct ovsrec_ssl *, enum ovsrec_ssl_column_id);

void ovsrec_ssl_verify_bootstrap_ca_cert(const struct ovsrec_ssl *);
void ovsrec_ssl_verify_ca_cert(const struct ovsrec_ssl *);
void ovsrec_ssl_verify_certificate(const struct ovsrec_ssl *);
void ovsrec_ssl_verify_external_ids(const struct ovsrec_ssl *);
void ovsrec_ssl_verify_private_key(const struct ovsrec_ssl *);

const struct ovsdb_datum *ovsrec_ssl_get_bootstrap_ca_cert(const struct ovsrec_ssl *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_ssl_get_ca_cert(const struct ovsrec_ssl *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_ssl_get_certificate(const struct ovsrec_ssl *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_ssl_get_external_ids(const struct ovsrec_ssl *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_ssl_get_private_key(const struct ovsrec_ssl *, enum ovsdb_atomic_type key_type);

void ovsrec_ssl_set_bootstrap_ca_cert(const struct ovsrec_ssl *, bool bootstrap_ca_cert);
void ovsrec_ssl_set_ca_cert(const struct ovsrec_ssl *, const char *ca_cert);
void ovsrec_ssl_set_certificate(const struct ovsrec_ssl *, const char *certificate);
void ovsrec_ssl_set_external_ids(const struct ovsrec_ssl *, const struct smap *);
void ovsrec_ssl_set_private_key(const struct ovsrec_ssl *, const char *private_key);

void ovsrec_ssl_add_clause_bootstrap_ca_cert(struct ovsdb_idl_condition *, enum ovsdb_function function, bool bootstrap_ca_cert);
unsigned int ovsrec_ssl_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_ssl_add_clause_ca_cert(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *ca_cert);
unsigned int ovsrec_ssl_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_ssl_add_clause_certificate(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *certificate);
unsigned int ovsrec_ssl_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_ssl_update_external_ids_setkey(const struct ovsrec_ssl *,  const char *, const char *);
void ovsrec_ssl_update_external_ids_delkey(const struct ovsrec_ssl *,  const char *);
void ovsrec_ssl_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_ssl_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_ssl_add_clause_private_key(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *private_key);
unsigned int ovsrec_ssl_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_ssl *ovsrec_ssl_index_init_row(struct ovsdb_idl_index *);
void ovsrec_ssl_index_set_bootstrap_ca_cert(const struct ovsrec_ssl *,
bool bootstrap_ca_cert);
void ovsrec_ssl_index_set_ca_cert(const struct ovsrec_ssl *,
const char *ca_cert);
void ovsrec_ssl_index_set_certificate(const struct ovsrec_ssl *,
const char *certificate);
void ovsrec_ssl_index_set_external_ids(const struct ovsrec_ssl *,
const struct smap *);
void ovsrec_ssl_index_set_private_key(const struct ovsrec_ssl *,
const char *private_key);

/* sFlow table. */
struct ovsrec_sflow {
	struct ovsdb_idl_row header_;

	/* agent column. */
	char *agent;

	/* external_ids column. */
	struct smap external_ids;

	/* header column. */
	int64_t *header;
	size_t n_header;

	/* polling column. */
	int64_t *polling;
	size_t n_polling;

	/* sampling column. */
	int64_t *sampling;
	size_t n_sampling;

	/* targets column. */
	char **targets;
	size_t n_targets;
};

enum ovsrec_sflow_column_id {
    OVSREC_SFLOW_COL_AGENT,
    OVSREC_SFLOW_COL_EXTERNAL_IDS,
    OVSREC_SFLOW_COL_HEADER,
    OVSREC_SFLOW_COL_POLLING,
    OVSREC_SFLOW_COL_SAMPLING,
    OVSREC_SFLOW_COL_TARGETS,
    OVSREC_SFLOW_N_COLUMNS
};

#define ovsrec_sflow_col_agent (ovsrec_sflow_columns[OVSREC_SFLOW_COL_AGENT])
#define ovsrec_sflow_col_external_ids (ovsrec_sflow_columns[OVSREC_SFLOW_COL_EXTERNAL_IDS])
#define ovsrec_sflow_col_header (ovsrec_sflow_columns[OVSREC_SFLOW_COL_HEADER])
#define ovsrec_sflow_col_polling (ovsrec_sflow_columns[OVSREC_SFLOW_COL_POLLING])
#define ovsrec_sflow_col_sampling (ovsrec_sflow_columns[OVSREC_SFLOW_COL_SAMPLING])
#define ovsrec_sflow_col_targets (ovsrec_sflow_columns[OVSREC_SFLOW_COL_TARGETS])

extern struct ovsdb_idl_column ovsrec_sflow_columns[OVSREC_SFLOW_N_COLUMNS];
bool ovsrec_server_has_sflow_table_col_agent(const struct ovsdb_idl *); 
bool ovsrec_server_has_sflow_table_col_external_ids(const struct ovsdb_idl *); 
bool ovsrec_server_has_sflow_table_col_header(const struct ovsdb_idl *); 
bool ovsrec_server_has_sflow_table_col_polling(const struct ovsdb_idl *); 
bool ovsrec_server_has_sflow_table_col_sampling(const struct ovsdb_idl *); 
bool ovsrec_server_has_sflow_table_col_targets(const struct ovsdb_idl *); 

bool ovsrec_server_has_sflow_table(const struct ovsdb_idl *);
const struct ovsrec_sflow_table *ovsrec_sflow_table_get(const struct ovsdb_idl *);
const struct ovsrec_sflow *ovsrec_sflow_table_first(const struct ovsrec_sflow_table *);

#define OVSREC_SFLOW_TABLE_FOR_EACH(ROW, TABLE) \
        for ((ROW) = ovsrec_sflow_table_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_sflow_next(ROW))
#define OVSREC_SFLOW_TABLE_FOR_EACH_SAFE_LONG(ROW, NEXT, TABLE) \
        for ((ROW) = ovsrec_sflow_table_first(TABLE); \
             (ROW) ? ((NEXT) = ovsrec_sflow_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_SFLOW_TABLE_FOR_EACH_SAFE_SHORT(ROW, TABLE) \
        for (const struct ovsrec_sflow * ROW__next = ((ROW) = ovsrec_sflow_table_first(TABLE), NULL); \
             (ROW) ? (ROW__next = ovsrec_sflow_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_SFLOW_TABLE_FOR_EACH_SAFE(...)                                        \
        OVERLOAD_SAFE_MACRO(OVSREC_SFLOW_TABLE_FOR_EACH_SAFE_LONG,                   \
                            OVSREC_SFLOW_TABLE_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)


const struct ovsrec_sflow *ovsrec_sflow_get_for_uuid(const struct ovsdb_idl *, const struct uuid *);
const struct ovsrec_sflow *ovsrec_sflow_table_get_for_uuid(const struct ovsrec_sflow_table *, const struct uuid *);
const struct ovsrec_sflow *ovsrec_sflow_first(const struct ovsdb_idl *);
const struct ovsrec_sflow *ovsrec_sflow_next(const struct ovsrec_sflow *);
#define OVSREC_SFLOW_FOR_EACH(ROW, IDL) \
        for ((ROW) = ovsrec_sflow_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_sflow_next(ROW))
#define OVSREC_SFLOW_FOR_EACH_SAFE_LONG(ROW, NEXT, IDL) \
        for ((ROW) = ovsrec_sflow_first(IDL); \
             (ROW) ? ((NEXT) = ovsrec_sflow_next(ROW), 1) : 0; \
             (ROW) = (NEXT))
#define OVSREC_SFLOW_FOR_EACH_SAFE_SHORT(ROW, IDL) \
        for (const struct ovsrec_sflow * ROW__next = ((ROW) = ovsrec_sflow_first(IDL), NULL); \
             (ROW) ? (ROW__next = ovsrec_sflow_next(ROW), 1) : (ROW__next = NULL, 0); \
             (ROW) = ROW__next)
#define OVSREC_SFLOW_FOR_EACH_SAFE(...)                                         \
        OVERLOAD_SAFE_MACRO(OVSREC_SFLOW_FOR_EACH_SAFE_LONG,                    \
                            OVSREC_SFLOW_FOR_EACH_SAFE_SHORT, 3, __VA_ARGS__)

unsigned int ovsrec_sflow_get_seqno(const struct ovsdb_idl *);
unsigned int ovsrec_sflow_row_get_seqno(const struct ovsrec_sflow *row, enum ovsdb_idl_change change);
const struct ovsrec_sflow *ovsrec_sflow_track_get_first(const struct ovsdb_idl *);
const struct ovsrec_sflow *ovsrec_sflow_track_get_next(const struct ovsrec_sflow *);
#define OVSREC_SFLOW_FOR_EACH_TRACKED(ROW, IDL) \
        for ((ROW) = ovsrec_sflow_track_get_first(IDL); \
             (ROW); \
             (ROW) = ovsrec_sflow_track_get_next(ROW))

const struct ovsrec_sflow *ovsrec_sflow_table_track_get_first(const struct ovsrec_sflow_table *);
#define OVSREC_SFLOW_TABLE_FOR_EACH_TRACKED(ROW, TABLE) \
        for ((ROW) = ovsrec_sflow_table_track_get_first(TABLE); \
             (ROW); \
             (ROW) = ovsrec_sflow_track_get_next(ROW))


/* Returns true if 'row' was inserted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally is new or it
 * may given unexpected results. */
static inline bool ovsrec_sflow_is_new(const struct ovsrec_sflow *row)
{
    return ovsrec_sflow_row_get_seqno(row, OVSDB_IDL_CHANGE_INSERT) > 0;
}

/* Returns true if 'row' was deleted since the last change tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * deleted or it may given unexpected results. */
static inline bool ovsrec_sflow_is_deleted(const struct ovsrec_sflow *row)
{
    return ovsrec_sflow_row_get_seqno(row, OVSDB_IDL_CHANGE_DELETE) > 0;
}

void ovsrec_sflow_index_destroy_row(const struct ovsrec_sflow *);

struct ovsrec_sflow *ovsrec_sflow_index_find(struct ovsdb_idl_index *, const struct ovsrec_sflow *);

int ovsrec_sflow_index_compare(
    struct ovsdb_idl_index *, 
    const struct ovsrec_sflow *, 
    const struct ovsrec_sflow *);
struct ovsdb_idl_cursor ovsrec_sflow_cursor_first(struct ovsdb_idl_index *);
struct ovsdb_idl_cursor ovsrec_sflow_cursor_first_eq(
    struct ovsdb_idl_index *, const struct ovsrec_sflow *);
struct ovsdb_idl_cursor ovsrec_sflow_cursor_first_ge(
    struct ovsdb_idl_index *, const struct ovsrec_sflow *);

struct ovsrec_sflow *ovsrec_sflow_cursor_data(struct ovsdb_idl_cursor *);

#define OVSREC_SFLOW_FOR_EACH_RANGE(ROW, FROM, TO, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_sflow_cursor_first_ge(INDEX, FROM); \
             (cursor__.position \
              && ((ROW) = ovsrec_sflow_cursor_data(&cursor__), \
                  !(TO) || ovsrec_sflow_index_compare(INDEX, ROW, TO) <= 0)); \
             ovsdb_idl_cursor_next(&cursor__))
#define OVSREC_SFLOW_FOR_EACH_EQUAL(ROW, KEY, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_sflow_cursor_first_eq(INDEX, KEY); \
             (cursor__.position \
              ? ((ROW) = ovsrec_sflow_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next_eq(&cursor__), \
                 true) \
              : false); \
            )
#define OVSREC_SFLOW_FOR_EACH_BYINDEX(ROW, INDEX) \
        for (struct ovsdb_idl_cursor cursor__ = ovsrec_sflow_cursor_first(INDEX); \
             (cursor__.position \
              ? ((ROW) = ovsrec_sflow_cursor_data(&cursor__), \
                 ovsdb_idl_cursor_next(&cursor__), \
                 true) \
              : false); \
            )

void ovsrec_sflow_init(struct ovsrec_sflow *);
void ovsrec_sflow_delete(const struct ovsrec_sflow *);
struct ovsrec_sflow *ovsrec_sflow_insert(struct ovsdb_idl_txn *);
struct ovsrec_sflow *ovsrec_sflow_insert_persist_uuid(
    struct ovsdb_idl_txn *txn, const struct uuid *uuid);

/* Returns true if the tracked column referenced by 'enum ovsrec_sflow_column_id' of
 * the row referenced by 'struct ovsrec_sflow *' was updated since the last change
 * tracking reset.
 *
 * Note: This can only be used to test rows of tracked changes. This cannot be
 * used to test if an uncommitted row that has been added locally has been
 * updated or it may given unexpected results. */
bool ovsrec_sflow_is_updated(const struct ovsrec_sflow *, enum ovsrec_sflow_column_id);

void ovsrec_sflow_verify_agent(const struct ovsrec_sflow *);
void ovsrec_sflow_verify_external_ids(const struct ovsrec_sflow *);
void ovsrec_sflow_verify_header(const struct ovsrec_sflow *);
void ovsrec_sflow_verify_polling(const struct ovsrec_sflow *);
void ovsrec_sflow_verify_sampling(const struct ovsrec_sflow *);
void ovsrec_sflow_verify_targets(const struct ovsrec_sflow *);

const struct ovsdb_datum *ovsrec_sflow_get_agent(const struct ovsrec_sflow *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_sflow_get_external_ids(const struct ovsrec_sflow *, enum ovsdb_atomic_type key_type, enum ovsdb_atomic_type value_type);
const struct ovsdb_datum *ovsrec_sflow_get_header(const struct ovsrec_sflow *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_sflow_get_polling(const struct ovsrec_sflow *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_sflow_get_sampling(const struct ovsrec_sflow *, enum ovsdb_atomic_type key_type);
const struct ovsdb_datum *ovsrec_sflow_get_targets(const struct ovsrec_sflow *, enum ovsdb_atomic_type key_type);

void ovsrec_sflow_set_agent(const struct ovsrec_sflow *, const char *agent);
void ovsrec_sflow_set_external_ids(const struct ovsrec_sflow *, const struct smap *);
void ovsrec_sflow_set_header(const struct ovsrec_sflow *, const int64_t *header, size_t n_header);
void ovsrec_sflow_set_polling(const struct ovsrec_sflow *, const int64_t *polling, size_t n_polling);
void ovsrec_sflow_set_sampling(const struct ovsrec_sflow *, const int64_t *sampling, size_t n_sampling);
void ovsrec_sflow_set_targets(const struct ovsrec_sflow *, const char **targets, size_t n_targets);

void ovsrec_sflow_update_agent_addvalue(const struct ovsrec_sflow *,  const char *);
void ovsrec_sflow_update_agent_delvalue(const struct ovsrec_sflow *,  const char *);
void ovsrec_sflow_add_clause_agent(struct ovsdb_idl_condition *, enum ovsdb_function function, const char *agent);
unsigned int ovsrec_sflow_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_sflow_update_external_ids_setkey(const struct ovsrec_sflow *,  const char *, const char *);
void ovsrec_sflow_update_external_ids_delkey(const struct ovsrec_sflow *,  const char *);
void ovsrec_sflow_add_clause_external_ids(struct ovsdb_idl_condition *, enum ovsdb_function function, const struct smap *);
unsigned int ovsrec_sflow_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_sflow_update_header_addvalue(const struct ovsrec_sflow *,  int64_t );
void ovsrec_sflow_update_header_delvalue(const struct ovsrec_sflow *,  int64_t );
void ovsrec_sflow_add_clause_header(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *header, size_t n_header);
unsigned int ovsrec_sflow_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_sflow_update_polling_addvalue(const struct ovsrec_sflow *,  int64_t );
void ovsrec_sflow_update_polling_delvalue(const struct ovsrec_sflow *,  int64_t );
void ovsrec_sflow_add_clause_polling(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *polling, size_t n_polling);
unsigned int ovsrec_sflow_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_sflow_update_sampling_addvalue(const struct ovsrec_sflow *,  int64_t );
void ovsrec_sflow_update_sampling_delvalue(const struct ovsrec_sflow *,  int64_t );
void ovsrec_sflow_add_clause_sampling(struct ovsdb_idl_condition *, enum ovsdb_function function, const int64_t *sampling, size_t n_sampling);
unsigned int ovsrec_sflow_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);
void ovsrec_sflow_update_targets_addvalue(const struct ovsrec_sflow *,  const char *);
void ovsrec_sflow_update_targets_delvalue(const struct ovsrec_sflow *,  const char *);
void ovsrec_sflow_add_clause_targets(struct ovsdb_idl_condition *, enum ovsdb_function function, const char **targets, size_t n_targets);
unsigned int ovsrec_sflow_set_condition(struct ovsdb_idl *, struct ovsdb_idl_condition *);

struct ovsrec_sflow *ovsrec_sflow_index_init_row(struct ovsdb_idl_index *);
void ovsrec_sflow_index_set_agent(const struct ovsrec_sflow *,
const char *agent);
void ovsrec_sflow_index_set_external_ids(const struct ovsrec_sflow *,
const struct smap *);
void ovsrec_sflow_index_set_header(const struct ovsrec_sflow *,
const int64_t *header, size_t n_header);
void ovsrec_sflow_index_set_polling(const struct ovsrec_sflow *,
const int64_t *polling, size_t n_polling);
void ovsrec_sflow_index_set_sampling(const struct ovsrec_sflow *,
const int64_t *sampling, size_t n_sampling);
void ovsrec_sflow_index_set_targets(const struct ovsrec_sflow *,
const char **targets, size_t n_targets);

enum ovsrec_table_id {
    OVSREC_TABLE_AUTOATTACH,
    OVSREC_TABLE_BRIDGE,
    OVSREC_TABLE_CT_TIMEOUT_POLICY,
    OVSREC_TABLE_CT_ZONE,
    OVSREC_TABLE_CONTROLLER,
    OVSREC_TABLE_DATAPATH,
    OVSREC_TABLE_FLOW_SAMPLE_COLLECTOR_SET,
    OVSREC_TABLE_FLOW_TABLE,
    OVSREC_TABLE_IPFIX,
    OVSREC_TABLE_INTERFACE,
    OVSREC_TABLE_MANAGER,
    OVSREC_TABLE_MIRROR,
    OVSREC_TABLE_NETFLOW,
    OVSREC_TABLE_OPEN_VSWITCH,
    OVSREC_TABLE_PORT,
    OVSREC_TABLE_QOS,
    OVSREC_TABLE_QUEUE,
    OVSREC_TABLE_SSL,
    OVSREC_TABLE_SFLOW,
    OVSREC_N_TABLES
};

#define ovsrec_table_autoattach (ovsrec_table_classes[OVSREC_TABLE_AUTOATTACH])
#define ovsrec_table_bridge (ovsrec_table_classes[OVSREC_TABLE_BRIDGE])
#define ovsrec_table_ct_timeout_policy (ovsrec_table_classes[OVSREC_TABLE_CT_TIMEOUT_POLICY])
#define ovsrec_table_ct_zone (ovsrec_table_classes[OVSREC_TABLE_CT_ZONE])
#define ovsrec_table_controller (ovsrec_table_classes[OVSREC_TABLE_CONTROLLER])
#define ovsrec_table_datapath (ovsrec_table_classes[OVSREC_TABLE_DATAPATH])
#define ovsrec_table_flow_sample_collector_set (ovsrec_table_classes[OVSREC_TABLE_FLOW_SAMPLE_COLLECTOR_SET])
#define ovsrec_table_flow_table (ovsrec_table_classes[OVSREC_TABLE_FLOW_TABLE])
#define ovsrec_table_ipfix (ovsrec_table_classes[OVSREC_TABLE_IPFIX])
#define ovsrec_table_interface (ovsrec_table_classes[OVSREC_TABLE_INTERFACE])
#define ovsrec_table_manager (ovsrec_table_classes[OVSREC_TABLE_MANAGER])
#define ovsrec_table_mirror (ovsrec_table_classes[OVSREC_TABLE_MIRROR])
#define ovsrec_table_netflow (ovsrec_table_classes[OVSREC_TABLE_NETFLOW])
#define ovsrec_table_open_vswitch (ovsrec_table_classes[OVSREC_TABLE_OPEN_VSWITCH])
#define ovsrec_table_port (ovsrec_table_classes[OVSREC_TABLE_PORT])
#define ovsrec_table_qos (ovsrec_table_classes[OVSREC_TABLE_QOS])
#define ovsrec_table_queue (ovsrec_table_classes[OVSREC_TABLE_QUEUE])
#define ovsrec_table_ssl (ovsrec_table_classes[OVSREC_TABLE_SSL])
#define ovsrec_table_sflow (ovsrec_table_classes[OVSREC_TABLE_SFLOW])

extern struct ovsdb_idl_table_class ovsrec_table_classes[OVSREC_N_TABLES];

extern struct ovsdb_idl_class ovsrec_idl_class;

const char * ovsrec_get_db_version(void);

#ifdef  __cplusplus
}
#endif

#endif /* OVSREC_IDL_HEADER */
