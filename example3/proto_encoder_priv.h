/**
  * @brief CAUTION: do not change this file - it is autogenerated.
  */

#include "proto.h"
#include <common/xroad_aux.h>

typedef struct
{
   uint16_t block_length;
   uint16_t template_id;
   uint16_t schema_id;
   uint16_t version;
} message_header_t;

typedef struct
{
   uint16_t length;
   char data[];
} var_string_t;

typedef struct
{
   uint16_t block_length;
   uint16_t num_in_group;
} group_size_encoding_t;

typedef struct
{
   proto_templates_t tid;
   char* data;
   size_t len;
   proto_logger_cback_t cback;
   size_t var_offset;
} encoder_t;

struct proto_group_encoder_s
{
   void* encoder;
   uint16_t idx;
   char* data;
};

typedef struct proto_group_encoder_s proto_group_encoder_t;

struct proto_default_encoder_s
{
   encoder_t base;
};

struct proto_MdBook_encoder_s
{
   encoder_t base;
   proto_group_encoder_t MdBook_bids_grp_encoder;
   proto_group_encoder_t MdBook_asks_grp_encoder;
};
struct proto_AccPosition_encoder_s
{
   encoder_t base;
   proto_group_encoder_t AccPosition_Position_grp_encoder;
};
struct proto_AccBalance_encoder_s
{
   encoder_t base;
   proto_group_encoder_t AccBalance_Balance_grp_encoder;
};
// types
typedef struct
{
   uint32_t length[1];
   uint8_t varData;
} VarStringType_t;
typedef struct
{
} LevelType_t;

// groups
typedef struct
{
   double level_price[1];
   double level_qty[1];
} MdBook_bids_t;

typedef struct
{
   double level_price[1];
   double level_qty[1];
} MdBook_asks_t;

typedef struct
{
   proto_Exchange_t exch;
   char account[16];
   char exch_account[16];
   char instr_name[32];
   double realized_pnl[1];
   double change_pnl[1];
   double unrealized_pnl[1];
   double position[1];
   double cost[1];
   char currency[3];
} AccPosition_Position_t;

typedef struct
{
   proto_Exchange_t exch;
   char account[16];
   char exch_account[16];
   char currency[3];
   double available[1];
} AccBalance_Balance_t;

// messages
typedef struct
{
   uint32_t req_id[1];
   char instr_name[32];
   char instr_class[4];
} InstrRequest_t;

typedef struct
{
   uint32_t req_id[1];
} RequestFailed_t;

typedef struct
{
   uint32_t req_id[1];
} RequestSucceed_t;

typedef struct
{
   uint32_t req_id[1];
   char instr_name[32];
   char cqg_name[32];
} InstrSetCQGNameRequest_t;

typedef struct
{
   uint32_t req_id[1];
   proto_Exchange_t exch;
} InstrListRequest_t;

typedef struct
{
   uint32_t req_id[1];
   uint64_t id[1];
   char instr_name[32];
   char instr_class[4];
   uint32_t precision[1];
   uint32_t lot_size[1];
   double tick_size[1];
   double tick_value[1];
   char currency[3];
   char cfi_code[6];
   uint64_t exp_date[1];
   uint8_t is_last[1];
   double strike[1];
   proto_Exchange_t exch;
   char cqgName[32];
} InstrumentDefinition_t;

typedef struct
{
   uint32_t req_id[1];
   uint64_t instr_id[1];
   proto_MdType_t type;
   proto_SubsActionType_t action;
   proto_FieldId_t field_id;
   char sender_id[32];
} MdSubscribe_t;

typedef struct
{
   uint32_t req_id[1];
   uint64_t instr_id[1];
   char sender_id[32];
   uint8_t force[1];
} MdUnsubscribe_t;

typedef struct
{
   uint32_t req_id[1];
   uint64_t instr_id[1];
   proto_MdType_t type;
   proto_FieldId_t field_id;
   proto_SubsResult_t result;
} MdSubscriptionResult_t;

typedef struct
{
   uint64_t instr_id[1];
   double price[1];
   double qty[1];
   proto_Side_t side;
   uint64_t exch_ts[1];
   uint64_t local_ts[1];
} MdTrade_t;

typedef struct
{
   uint64_t instr_id[1];
   double bid_price[1];
   double bid_qty[1];
   double ask_price[1];
   double ask_qty[1];
   uint64_t exch_ts[1];
   uint64_t local_ts[1];
} MdQuote_t;

typedef struct
{
   uint64_t instr_id[1];
} MdBook_t;

typedef struct
{
   uint64_t instr_id[1];
   uint64_t exch_ts[1];
   uint64_t local_ts[1];
   proto_FieldId_t field_id;
   double field_val[1];
} MdStatistic_t;

typedef struct
{
   uint32_t req_id[1];
   proto_SubsActionType_t action;
} AccPosSubscribe_t;

typedef struct
{
   uint32_t req_id[1];
} AccPosUnsubscribe_t;

typedef struct
{
   uint32_t req_id[1];
   proto_SubsResult_t result;
} AccPosSubscriptionResult_t;

typedef struct
{
   uint32_t req_id[1];
   proto_SubsActionType_t action;
} AccBalanceSubscribe_t;

typedef struct
{
   uint32_t req_id[1];
} AccBalanceUnsubscribe_t;

typedef struct
{
   uint32_t req_id[1];
   proto_SubsResult_t result;
} AccBalanceSubscriptionResult_t;

typedef struct
{
} AccPosition_t;

typedef struct
{
} AccBalance_t;

typedef struct
{
   uint64_t instr_id[1];
   int64_t clord_id[1];
   double price[1];
   double qty[1];
   proto_Side_t side;
   proto_TimeInForce_t time_in_force;
   proto_OrdType_t ord_type;
   char account[16];
   char client_code[16];
   proto_AlgoType_t algo_type;
   uint32_t algo_start[1];
   uint32_t algo_stop[1];
   uint8_t algo_aggr_level[1];
   uint8_t algo_mid_time[1];
   uint8_t algo_aggr_time[1];
   float algo_price_move[1];
   uint32_t algo_working_int[1];
   uint32_t algo_book_depth[1];
   uint32_t algo_level_dist[1];
   double algo_display_qty[1];
   uint32_t algo_sensitivity[1];
   uint32_t algo_deviation[1];
   double algo_threshold[1];
} NewOrderSingle_t;

typedef struct
{
   int64_t clord_id[1];
   uint64_t exch_id[1];
   uint64_t ts[1];
} OrderAccepted_t;

typedef struct
{
   int64_t clord_id[1];
   uint64_t ts[1];
   proto_OrdRejReason_t ord_rej_reason;
   uint32_t text_length[1];
   uint8_t text_varData;
} OrderRejected_t;

typedef struct
{
   int64_t clord_id[1];
} CancelOrder_t;

typedef struct
{
   int64_t clord_id[1];
   uint64_t ts[1];
   proto_OrdRejReason_t rej_reason;
   uint32_t text_length[1];
   uint8_t text_varData;
} CancelOrderRejected_t;

typedef struct
{
   int64_t clord_id[1];
   uint64_t ts[1];
} OrderCanceled_t;

typedef struct
{
   int64_t clord_id[1];
   double price[1];
   double qty[1];
   uint32_t algo_start[1];
   uint32_t algo_stop[1];
   uint8_t algo_aggr_level[1];
   uint8_t algo_mid_time[1];
   uint8_t algo_aggr_time[1];
   float algo_price_move[1];
   uint32_t algo_working_int[1];
   uint32_t algo_book_depth[1];
   uint32_t algo_level_dist[1];
   double algo_display_qty[1];
   uint32_t algo_sensitivity[1];
   uint32_t algo_deviation[1];
   double algo_threshold[1];
} ReplaceOrder_t;

typedef struct
{
   int64_t clord_id[1];
   uint64_t ts[1];
   proto_OrdRejReason_t rej_reason;
   uint32_t text_length[1];
   uint8_t text_varData;
} ReplaceOrderRejected_t;

typedef struct
{
   int64_t clord_id[1];
   uint64_t ts[1];
   double price[1];
   double qty[1];
} OrderReplaced_t;

typedef struct
{
   int64_t clord_id[1];
   uint64_t exch_id[1];
   uint64_t ts[1];
   double price[1];
   double qty[1];
   double leaves_qty[1];
   double cum_qty[1];
} Trade_t;

typedef struct
{
   int64_t clord_id[1];
   uint64_t ts[1];
} OrderExpired_t;

typedef struct
{
   int64_t tradeno[1];
   uint64_t orderno[1];
   char instr_name[32];
   char account[16];
   char client_code[16];
   uint64_t ts[1];
   double price[1];
   double qty[1];
   double fee[1];
   proto_Side_t side;
} TrdCaptReport_t;

typedef struct
{
   uint32_t req_id[1];
   uint64_t ts[1];
} Ping_t;

typedef struct
{
   uint32_t req_id[1];
   uint64_t ts[1];
} Pong_t;

typedef struct
{
   proto_State_t state;
   uint64_t ts[1];
} SystemState_t;

typedef struct
{
   uint64_t ts[1];
} Heartbeat_t;

