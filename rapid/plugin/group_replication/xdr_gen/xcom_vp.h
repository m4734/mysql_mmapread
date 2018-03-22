/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _XCOM_VP_H_RPCGEN
#define _XCOM_VP_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

/* Copyright (c) 2010, 2017, Oracle and/or its affiliates. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA */

#include "xcom_vp_platform.h"

enum xcom_proto {
	x_unknown_proto = 0,
	x_1_0 = 1,
	x_1_1 = 2,
	x_1_2 = 3,
};
typedef enum xcom_proto xcom_proto;


struct x_proto_range {
	xcom_proto min_proto;
	xcom_proto max_proto;
};
typedef struct x_proto_range x_proto_range;

enum delivery_status {
	delivery_ok = 0,
	delivery_failure = 1,
};
typedef enum delivery_status delivery_status;

enum cons_type {
	cons_majority = 0,
	cons_all = 1,
	cons_none = 2,
};
typedef enum cons_type cons_type;

typedef uint32_t node_no;

struct synode_no {
	uint32_t group_id;
	uint64_t msgno;
	node_no node;
};
typedef struct synode_no synode_no;

struct trans_id {
	synode_no cfg;
	uint32_t pc;
};
typedef struct trans_id trans_id;

typedef struct {
	u_int node_set_len;
	bool_t *node_set_val;
} node_set;

struct blob {
	struct {
		u_int data_len;
		char *data_val;
	} data;
};
typedef struct blob blob;

struct node_address_1_0 {
	char *address;
	blob uuid;
};
typedef struct node_address_1_0 node_address_1_0;

typedef struct {
	u_int node_list_1_0_len;
	node_address_1_0 *node_list_1_0_val;
} node_list_1_0;

struct node_address {
	char *address;
	blob uuid;
	x_proto_range proto;
};
typedef struct node_address node_address;

typedef struct {
	u_int node_list_len;
	node_address *node_list_val;
} node_list;
/*
	Custom xdr functions to coerce rpcgen into handling different protocol versions.
	Protocol version is passed in an extended XDR object.
*/

#ifndef VERSION_CONTROL
#define VERSION_CONTROL

extern xcom_proto const my_min_xcom_version; /* The minimum protocol version I am able to understand */
extern xcom_proto const my_xcom_version; /* The maximum protocol version I am able to understand */

typedef node_list node_list_1_1; /* Alias for real type to avoid generating xdr call to xdr_node_list */

extern bool_t xdr_node_list_1_1 (XDR *, node_list_1_1*);

#endif
#ifndef CHECKED_DATA
#define CHECKED_DATA
typedef struct {
 u_int data_len;
 char *data_val;
} checked_data;
extern bool_t xdr_checked_data (XDR *, checked_data*);
#endif

enum cargo_type {
	unified_boot_type = 0,
	xcom_boot_type = 1,
	xcom_set_group = 2,
	xcom_recover = 3,
	app_type = 4,
	query_type = 5,
	query_next_log = 6,
	exit_type = 7,
	reset_type = 8,
	begin_trans = 9,
	prepared_trans = 10,
	abort_trans = 11,
	view_msg = 12,
	remove_reset_type = 13,
	add_node_type = 14,
	remove_node_type = 15,
	enable_arbitrator = 16,
	disable_arbitrator = 17,
	force_config_type = 18,
	x_terminate_and_exit = 19,
	set_cache_limit = 20,
};
typedef enum cargo_type cargo_type;

typedef struct {
	u_int node_no_array_len;
	node_no *node_no_array_val;
} node_no_array;

typedef struct {
	u_int synode_no_array_len;
	synode_no *synode_no_array_val;
} synode_no_array;

struct uncommitted_list {
	uint32_t active;
	synode_no_array vers;
};
typedef struct uncommitted_list uncommitted_list;

struct repository {
	synode_no vers;
	synode_no_array msg_list;
	uncommitted_list u_list;
};
typedef struct repository repository;

struct x_error {
	int32_t nodeid;
	int32_t code;
	char *message;
};
typedef struct x_error x_error;

struct trans_data {
	trans_id tid;
	int32_t pc;
	char *cluster_name;
	x_error errmsg;
};
typedef struct trans_data trans_data;

struct app_u {
	cargo_type c_t;
	union {
		node_list_1_1 nodes;
		repository rep;
		checked_data data;
		trans_data td;
		node_set present;
		uint64_t cache_limit;
	} app_u_u;
};
typedef struct app_u app_u;

enum recover_action {
	rec_block = 0,
	rec_delay = 1,
	rec_send = 2,
};
typedef enum recover_action recover_action;

struct app_data {
	synode_no unique_id;
	uint32_t group_id;
	uint64_t lsn;
	synode_no app_key;
	cons_type consensus;
	double expiry_time;
	bool_t notused;
	bool_t log_it;
	bool_t chosen;
	recover_action recover;
	app_u body;
	struct app_data *next;
};
typedef struct app_data app_data;

typedef app_data *app_data_ptr;

typedef struct {
	u_int app_data_ptr_array_len;
	app_data_ptr *app_data_ptr_array_val;
} app_data_ptr_array;

typedef app_data_ptr *app_data_list;

struct key_range {
	synode_no k1;
	synode_no k2;
};
typedef struct key_range key_range;

typedef uint32_t bit_mask;

#define BITS_PER_BYTE 8
#define MASK_BITS ((uint32_t)(sizeof (bit_mask) * BITS_PER_BYTE)) /* bits per mask */
#define howmany_words(x, y) (((x)+((y)-1))/(y))


struct bit_set {
	struct {
		u_int bits_len;
		bit_mask *bits_val;
	} bits;
};
typedef struct bit_set bit_set;
#define BIT_OP(__n, __p, __op, __inv) ((__p)->bits.bits_val[(__n)/MASK_BITS] __op __inv (1u << ((__n) % MASK_BITS)))
#define BIT_XOR(__n, __p) BIT_OP(__n, __p, ^=, )
#define BIT_SET(__n, __p) BIT_OP(__n, __p, |=, )
#define BIT_CLR(__n, __p) BIT_OP(__n, __p, &=, ~)
#define BIT_ISSET(__n, __p) (BIT_OP(__n, __p, &, ) != 0ul)
#define BIT_ZERO(__p) memset((__p)->bits.bits_val, 0, (__p)->bits.bits_len * sizeof(*(__p)->bits.bits_val))
extern bit_set *new_bit_set(uint32_t bits);
extern bit_set *clone_bit_set(bit_set *orig);
extern void free_bit_set(bit_set *bs);

struct ballot {
	int32_t cnt;
	node_no node;
};
typedef struct ballot ballot;

enum pax_op {
	client_msg = 0,
	initial_op = 1,
	prepare_op = 2,
	ack_prepare_op = 3,
	ack_prepare_empty_op = 4,
	accept_op = 5,
	ack_accept_op = 6,
	learn_op = 7,
	recover_learn_op = 8,
	multi_prepare_op = 9,
	multi_ack_prepare_empty_op = 10,
	multi_accept_op = 11,
	multi_ack_accept_op = 12,
	multi_learn_op = 13,
	skip_op = 14,
	i_am_alive_op = 15,
	are_you_alive_op = 16,
	need_boot_op = 17,
	snapshot_op = 18,
	die_op = 19,
	read_op = 20,
	gcs_snapshot_op = 21,
	xcom_client_reply = 22,
	tiny_learn_op = 23,
	LAST_OP = 24,
};
typedef enum pax_op pax_op;

enum pax_msg_type {
	normal = 0,
	no_op = 1,
	multi_no_op = 2,
};
typedef enum pax_msg_type pax_msg_type;

enum start_t {
	IDLE = 0,
	BOOT = 1,
	RECOVER = 2,
};
typedef enum start_t start_t;

struct snapshot {
	synode_no vers;
	app_data_ptr_array snap;
	uncommitted_list u_list;
};
typedef struct snapshot snapshot;

struct config {
	synode_no start;
	synode_no boot_key;
	node_list_1_1 nodes;
};
typedef struct config config;

typedef config *config_ptr;

typedef struct {
	u_int configs_len;
	config_ptr *configs_val;
} configs;

struct gcs_snapshot {
	synode_no log_start;
	configs cfg;
	blob app_snap;
};
typedef struct gcs_snapshot gcs_snapshot;

enum client_reply_code {
	REQUEST_OK = 0,
	REQUEST_FAIL = 1,
	REQUEST_RETRY = 2,
};
typedef enum client_reply_code client_reply_code;

struct pax_msg_1_1 {
	node_no to;
	node_no from;
	uint32_t group_id;
	synode_no max_synode;
	start_t start_type;
	ballot reply_to;
	ballot proposal;
	pax_op op;
	synode_no synode;
	pax_msg_type msg_type;
	bit_set *receivers;
	app_data *a;
	snapshot *snap;
	gcs_snapshot *gcs_snap;
	client_reply_code cli_err;
	bool_t force_delivery;
	int32_t refcnt;
};
typedef struct pax_msg_1_1 pax_msg_1_1;

struct pax_msg_1_2 {
	node_no to;
	node_no from;
	uint32_t group_id;
	synode_no max_synode;
	start_t start_type;
	ballot reply_to;
	ballot proposal;
	pax_op op;
	synode_no synode;
	pax_msg_type msg_type;
	bit_set *receivers;
	app_data *a;
	snapshot *snap;
	gcs_snapshot *gcs_snap;
	client_reply_code cli_err;
	bool_t force_delivery;
	int32_t refcnt;
	synode_no delivered_msg;
};
typedef struct pax_msg_1_2 pax_msg_1_2;
#ifndef PAX_MSG_TYPEDEF
#define PAX_MSG_TYPEDEF
typedef pax_msg_1_2 pax_msg;
extern bool_t xdr_pax_msg (XDR *, pax_msg*);
#endif

typedef char *file_name;

typedef struct {
	u_int file_name_array_len;
	file_name *file_name_array_val;
} file_name_array;

struct file_copy_data {
	char *clustername;
	char *copydir;
	char *server;
	int32_t copy_port;
};
typedef struct file_copy_data file_copy_data;

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_xcom_proto (XDR *, xcom_proto*);
extern  bool_t xdr_xcom_proto (XDR *, xcom_proto*);
extern  bool_t xdr_x_proto_range (XDR *, x_proto_range*);
extern  bool_t xdr_delivery_status (XDR *, delivery_status*);
extern  bool_t xdr_cons_type (XDR *, cons_type*);
extern  bool_t xdr_node_no (XDR *, node_no*);
extern  bool_t xdr_synode_no (XDR *, synode_no*);
extern  bool_t xdr_trans_id (XDR *, trans_id*);
extern  bool_t xdr_node_set (XDR *, node_set*);
extern  bool_t xdr_blob (XDR *, blob*);
extern  bool_t xdr_node_address_1_0 (XDR *, node_address_1_0*);
extern  bool_t xdr_node_list_1_0 (XDR *, node_list_1_0*);
extern  bool_t xdr_node_address (XDR *, node_address*);
extern  bool_t xdr_node_list (XDR *, node_list*);
extern  bool_t xdr_cargo_type (XDR *, cargo_type*);
extern  bool_t xdr_node_no_array (XDR *, node_no_array*);
extern  bool_t xdr_synode_no_array (XDR *, synode_no_array*);
extern  bool_t xdr_uncommitted_list (XDR *, uncommitted_list*);
extern  bool_t xdr_repository (XDR *, repository*);
extern  bool_t xdr_x_error (XDR *, x_error*);
extern  bool_t xdr_trans_data (XDR *, trans_data*);
extern  bool_t xdr_app_u (XDR *, app_u*);
extern  bool_t xdr_recover_action (XDR *, recover_action*);
extern  bool_t xdr_app_data (XDR *, app_data*);
extern  bool_t xdr_app_data_ptr (XDR *, app_data_ptr*);
extern  bool_t xdr_app_data_ptr_array (XDR *, app_data_ptr_array*);
extern  bool_t xdr_app_data_list (XDR *, app_data_list*);
extern  bool_t xdr_key_range (XDR *, key_range*);
extern  bool_t xdr_bit_mask (XDR *, bit_mask*);
extern  bool_t xdr_bit_set (XDR *, bit_set*);
extern  bool_t xdr_ballot (XDR *, ballot*);
extern  bool_t xdr_pax_op (XDR *, pax_op*);
extern  bool_t xdr_pax_msg_type (XDR *, pax_msg_type*);
extern  bool_t xdr_start_t (XDR *, start_t*);
extern  bool_t xdr_snapshot (XDR *, snapshot*);
extern  bool_t xdr_config (XDR *, config*);
extern  bool_t xdr_config_ptr (XDR *, config_ptr*);
extern  bool_t xdr_configs (XDR *, configs*);
extern  bool_t xdr_gcs_snapshot (XDR *, gcs_snapshot*);
extern  bool_t xdr_client_reply_code (XDR *, client_reply_code*);
extern  bool_t xdr_pax_msg_1_1 (XDR *, pax_msg_1_1*);
extern  bool_t xdr_pax_msg_1_2 (XDR *, pax_msg_1_2*);
extern  bool_t xdr_file_name (XDR *, file_name*);
extern  bool_t xdr_file_name_array (XDR *, file_name_array*);
extern  bool_t xdr_file_copy_data (XDR *, file_copy_data*);

#else /* K&R C */
extern bool_t xdr_xcom_proto ();
extern bool_t xdr_xcom_proto ();
extern bool_t xdr_x_proto_range ();
extern bool_t xdr_delivery_status ();
extern bool_t xdr_cons_type ();
extern bool_t xdr_node_no ();
extern bool_t xdr_synode_no ();
extern bool_t xdr_trans_id ();
extern bool_t xdr_node_set ();
extern bool_t xdr_blob ();
extern bool_t xdr_node_address_1_0 ();
extern bool_t xdr_node_list_1_0 ();
extern bool_t xdr_node_address ();
extern bool_t xdr_node_list ();
extern bool_t xdr_cargo_type ();
extern bool_t xdr_node_no_array ();
extern bool_t xdr_synode_no_array ();
extern bool_t xdr_uncommitted_list ();
extern bool_t xdr_repository ();
extern bool_t xdr_x_error ();
extern bool_t xdr_trans_data ();
extern bool_t xdr_app_u ();
extern bool_t xdr_recover_action ();
extern bool_t xdr_app_data ();
extern bool_t xdr_app_data_ptr ();
extern bool_t xdr_app_data_ptr_array ();
extern bool_t xdr_app_data_list ();
extern bool_t xdr_key_range ();
extern bool_t xdr_bit_mask ();
extern bool_t xdr_bit_set ();
extern bool_t xdr_ballot ();
extern bool_t xdr_pax_op ();
extern bool_t xdr_pax_msg_type ();
extern bool_t xdr_start_t ();
extern bool_t xdr_snapshot ();
extern bool_t xdr_config ();
extern bool_t xdr_config_ptr ();
extern bool_t xdr_configs ();
extern bool_t xdr_gcs_snapshot ();
extern bool_t xdr_client_reply_code ();
extern bool_t xdr_pax_msg_1_1 ();
extern bool_t xdr_pax_msg_1_2 ();
extern bool_t xdr_file_name ();
extern bool_t xdr_file_name_array ();
extern bool_t xdr_file_copy_data ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_XCOM_VP_H_RPCGEN */
