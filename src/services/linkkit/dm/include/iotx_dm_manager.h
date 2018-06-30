#ifndef _IOTX_DM_MANAGER_H_
#define _IOTX_DM_MANAGER_H_

#include "iotx_dm_shadow.h"
#include "lite-cjson.h"
#include "iot_export_dm.h"

#define IOTX_DMGR_DEV_SUB_TIMEOUT_MS (5000)

#define IOTX_DMGR_DEV_SUB_START      (-1)
#define IOTX_DMGR_DEV_SUB_END        (-2)

typedef struct {
	int generic_index;
	int service_event_index;
	int service_event_number;
	char **service_event;
	uint64_t ctime;
}iotx_dmgr_dev_sub_t;

typedef struct {
	int devid;
	int dev_type;
	iotx_dsw_t *dev_shadow;
	char product_key[PRODUCT_KEY_MAXLEN];
	char device_name[DEVICE_NAME_MAXLEN];
	char device_secret[DEVICE_SECRET_MAXLEN];
	iotx_dm_dev_avail_t status;
	iotx_dm_dev_status_t dev_status;
	iotx_dmgr_dev_sub_t sub_status;
	struct list_head linked_list;
}iotx_dmgr_dev_node_t;

typedef struct {
	void *mutex;
	int global_devid;
	struct list_head dev_list;
}iotx_dmgr_ctx;

int iotx_dmgr_init(void);
int iotx_dmgr_deinit(void);
int iotx_dmgr_device_create(_IN_ int dev_type, _IN_ char product_key[PRODUCT_KEY_MAXLEN], _IN_ char device_name[DEVICE_NAME_MAXLEN], _OU_ int *devid);
int iotx_dmgr_device_destroy(_IN_ int devid);
int iotx_dmgr_device_number(void);
int iotx_dmgr_get_devid_by_index(_IN_ int index, _OU_ int *devid);
int iotx_dmgr_get_next_devid(_IN_ int devid, _OU_ int *devid_next);
int iotx_dmgr_search_device_by_devid(_IN_ int devid, _OU_ char product_key[PRODUCT_KEY_MAXLEN], _OU_ char device_name[DEVICE_NAME_MAXLEN], _OU_ char device_secret[DEVICE_SECRET_MAXLEN]);
int iotx_dmgr_search_device_by_pkdn(_IN_ char product_key[PRODUCT_KEY_MAXLEN], _IN_ char device_name[DEVICE_NAME_MAXLEN], _OU_ int *devid);
int iotx_dmgr_search_device_node_by_devid(_IN_ int devid, _OU_ void **node);
int iotx_dmgr_search_devid_by_device_node(_IN_ void *node, _OU_ int *devid);
int iotx_dmgr_get_dev_type(_IN_ int devid, _OU_ int *dev_type);
int iotx_dmgr_set_dev_enable(_IN_ int devid);
int iotx_dmgr_set_dev_disable(_IN_ int devid);
int iotx_dmgr_get_dev_avail(_IN_ char product_key[PRODUCT_KEY_MAXLEN], _IN_ char device_name[DEVICE_NAME_MAXLEN], _OU_ iotx_dm_dev_avail_t *status);
int iotx_dmgr_set_dev_status(_IN_ int devid, _IN_ iotx_dm_dev_status_t status);
int iotx_dmgr_get_dev_status(_IN_ int devid, _OU_ iotx_dm_dev_status_t *status);
int iotx_dmgr_set_dev_sub_generic_index(_IN_ int devid, _IN_ int index);
int iotx_dmgr_get_dev_sub_generic_index(_IN_ int devid, _OU_ int *index);
int iotx_dmgr_set_dev_sub_service_event(_IN_ int devid, _IN_ int number, _IN_ char **service_event);
int iotx_dmgr_set_dev_sub_service_event_index(_IN_ int devid, _IN_ int index);
int iotx_dmgr_get_dev_sub_service_event_number(_IN_ int devid, _OU_ int *number);
int iotx_dmgr_get_dev_sub_service_event_index(_IN_ int devid, _OU_ int *index);
int iotx_dmgr_get_dev_sub_service_event(_IN_ int devid, _IN_ int index, _OU_ char **service_event);
int iotx_dmgr_clear_dev_sub_service_event(_IN_ int devid);

void iotx_dmgr_dev_sub_status_check(void);
int iotx_dmgr_set_tsl(int devid, iotx_dm_tsl_type_t tsl_type, const char *tsl, int tsl_len);
int iotx_dmgr_get_product_key(_IN_ int devid, _OU_ char product_key[PRODUCT_KEY_MAXLEN]);
int iotx_dmgr_get_device_name(_IN_ int devid, _OU_ char device_name[DEVICE_NAME_MAXLEN]);
int iotx_dmgr_set_device_secret(_IN_ int devid, _IN_ char device_secret[DEVICE_SECRET_MAXLEN]);
int iotx_dmgr_get_device_secret(_IN_ int devid, _OU_ char device_secret[DEVICE_SECRET_MAXLEN]);
int iotx_dmgr_get_property_data(_IN_ int devid, _IN_ char *key, _IN_ int key_len, _OU_ void **data);
int iotx_dmgr_get_service_input_data(_IN_ int devid, _IN_ char *key, _IN_ int key_len, _OU_ void **data);
int iotx_dmgr_get_data_type(_IN_ void *property, _OU_ iotx_dsw_data_type_e *type);
int iotx_dmgr_get_property_number(_IN_ int devid, _OU_ int *number);
int iotx_dmgr_get_service_number(_IN_ int devid, _OU_ int *number);
int iotx_dmgr_get_event_number(_IN_ int devid, _OU_ int *number);
int iotx_dmgr_get_property_by_index(_IN_ int devid, _IN_ int index, _OU_ void **property);
int iotx_dmgr_get_service_by_index(_IN_ int devid, _IN_ int index, _OU_ void **service);
int iotx_dmgr_get_event_by_index(_IN_ int devid, _IN_ int index, _OU_ void **event);
int iotx_dmgr_get_service_by_identifier(_IN_ int devid, _IN_ char *identifier, _OU_ void **service);
int iotx_dmgr_get_event_by_identifier(_IN_ int devid, _IN_ char *identifier, _OU_ void **event);
int iotx_dmgr_get_property_identifier(_IN_ void *property, _OU_ char **identifier);
int iotx_dmgr_get_service_method(_IN_ void *service, _OU_ char **method);
int iotx_dmgr_get_event_method(_IN_ void *event, _OU_ char **method);
int iotx_dmgr_set_property_value(_IN_ int devid, _IN_ char *key, _IN_ int key_len, _IN_ void *value, _IN_ int value_len);
int iotx_dmgr_get_property_value(_IN_ int devid, _IN_ char *key, _IN_ int key_len, _IN_ void *value);
int iotx_dmgr_set_event_output_value(_IN_ int devid, _IN_ char * key,_IN_ int key_len,_IN_ void * value,_IN_ int value_len);
int iotx_dmgr_get_event_output_value(_IN_ int devid, _IN_ char *key, _IN_ int key_len, _IN_ void *value);
int iotx_dmgr_set_service_input_value(_IN_ int devid, _IN_ char * key,_IN_ int key_len,_IN_ void * value,_IN_ int value_len);
int iotx_dmgr_get_service_input_value(_IN_ int devid, _IN_ char *key, _IN_ int key_len, _IN_ void *value);
int iotx_dmgr_set_service_output_value(_IN_ int devid, _IN_ char * key,_IN_ int key_len,_IN_ void * value,_IN_ int value_len);
int iotx_dmgr_get_service_output_value(_IN_ int devid, _IN_ char *key, _IN_ int key_len, _IN_ void *value);
int iotx_dmgr_assemble_property(_IN_ int devid, _IN_ char *identifier, _IN_ int identifier_len, _IN_ lite_cjson_item_t *lite);
int iotx_dmgr_assemble_event_output(_IN_ int devid, _IN_ char *identifier, _IN_ int identifier_len, _IN_ lite_cjson_item_t *lite);
int iotx_dmgr_assemble_service_output(_IN_ int devid, _IN_ char *identifier, _IN_ int identifier_len, _IN_ lite_cjson_item_t *lite);

#endif
