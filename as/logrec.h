#pragma once

// TICKET----------------------------------------------------------------------
typedef struct 
{
	double load_qty;
	char   name[9];
	char   desc[17];
	char   um[5];
	double price;
	double amount;
	double order_qty;
	double cum_qty;
	char   long_desc[41];
	char   price_um[13];
} TICKET_PRODUCT;

// TICKET ---------------------------------------------------------------------
typedef struct 
{
	short plant_num;				// 01
	long  ticket_num;				// 02
	short truck_num;				// 03
	double load_size;				// 04
	char  mix_code[11];				// 05
	char  mix_desc[25];				// 06
	double slump;					// 07
	char  use[17];					// 08
	char  date[10];					// 09

	char  customer_code[9];			// 10
	char  customer_name_1[33];		// 11
	char  customer_name_2[33];		// 12
	char  customer_name_3[33];		// 13
	long  driver_num;				// 14
	char  driver_name[33];			// 15
	char  del_addr_1[33];			// 16
	char  del_addr_2[33];			// 17
	char  po_number[17];			// 18
	long  order_num;				// 19

	double quantity;				// 20
	char  del_inst_1[33];			// 21
	char  del_inst_2[33];			// 22
	char  del_inst_3[33];			// 23
	short tax_code;					// 24
	char  time_due[6];				// 25
	char  reserved[9];				// 26
	double cum_qty;					// 27
	double ordered_qty;				// 28
	char  mix_prod_code[9];			// 29

	char  mix_prod_desc[41];		// 30

	char  unit[5];					// 31
	double mix_price;				// 32
	double mix_ext_amount;			// 33
									// 34..69 in products

	char   min_load_charge_prt[25]; // 70
	double min_load_charge_amt;     // 71
	double subtotal;				// 72
	double tax_total;				// 73
	double order_cum_total;			// 74
	char   time_sent[6];			// 75		
	char   zone[9];					// 76		
	char   project_code[17];		// 77				
	char   ordered_by[25];			// 78				
	char   special_inst_1[33];		// 79	

	char   special_inst_2[33];		// 80					
	char   operator_msg[33];		// 81					
	char   local_ticket_change;		// 82			
	char   lot_num[9];				// 83		
	char   project_phone[13];		// 84
	char   percent_calcium[5];		// 85
	char   percent_air_ent[5];		// 86
	char   super_plasticizer[5];	// 87
									// 88..91 spare
	double  num_percent_calcium;	// 92
	short  num_percent_air;			// 93
	short  num_super_plasticizer;	// 94
	short  percent_hot_water;		// 95
	short  pounds_of_ice;			// 96
	short  loads_delivered;			// 97		
	char   admix_code[4];			// 98		
	char   job_name[17];			// 99		
	char   print_weights;			// 100
	
	//-------------------------------------------TMIX 101..142
	char  mix_code_1[9];			// 101									
	char  mix_desc_1[25];			// 102	
	char  agg_1_name[9];			// 103								
	short agg_1_weight;				// 104
	char  agg_2_name[9];			// 105								
	short agg_2_weight;				// 106
	char  agg_3_name[9];			// 107								
	short agg_3_weight;				// 108
	char  agg_4_name[9];			// 109								
	short agg_4_weight;				// 110
	
	char  cement_1_name[9];			// 111								
	short cement_1_weight;			// 112
	char  cement_2_name[9];			// 113
	short cement_2_weight;			// 114
	char  water_1_name[9];			// 115								
	double water_1_weight;			// 116	
	char  admix_1_name[9];			// 117								
	double admix_1_ozs;				// 118
	char  admix_2_name[9];			// 119								
	double admix_2_ozs;				// 120
	
	char  admix_3_name[9];			// 121								
	double admix_3_ozs;				// 122
	char  admix_4_name[9];			// 123								
	double admix_4_ozs;				// 124
	char  admix_5_name[9];			// 125								
	double admix_5_ozs;				// 126
	char  admix_6_name[9];			// 127								
	double admix_6_ozs;				// 128
	char  cement_3_name[9];			// 129
	short cement_3_weight;			// 130
	
	char  water_2_name[9];			// 131								
	double water_2_weight;			// 132
	short mixer_time;				// 133
	double max_load_size;			// 134
	char  agg_5_name[9];			// 135								
	short agg_5_weight;				// 136
	double  percent_air;			// 137							
	double  slump_target;			// 138							
	double max_dry_load_size;		// 139
	double max_async_load_size;		// 140
								
	char  agg_moist_ref;			// 141
	char  metric;					// 142
	//------------------------------------------------------------------
									// 143..148 reserved								
    short zone_travel;				// 149	    
  	char  mix_desc_ex[33];			// 150
  	
  	char  weighmaster_name[33];		// 151
  	char  begin_unload_time[33];	// 152
    char user_defined_4[33];		// 153			silo #
	char user_defined_5[33];		// 154			# of drops
	char user_defined_6[33];		// 155			tare ??
	char user_defined_7[33];		// 156          tax percent
	char user_defined_8[33];		// 157	        print only
	char user_defined_9[33];
	char user_defined_10[33];
	char user_defined_11[33];
	char user_defined_12[33];
	char user_defined_13[33];
	char user_defined_14[33];
	char user_defined_15[33];
	char user_defined_16[33];
	char user_defined_17[33];
	char user_defined_18[33];
	char user_defined_19[33];
	char user_defined_20[33];
	char user_defined_21[33];
	char user_defined_22[33];
	char user_defined_23[33];
	char user_defined_24[33];
	char user_defined_25[33];
	char user_defined_26[33];
	char user_defined_27[33];
	char user_defined_28[33];
	char user_defined_29[33];
	char user_defined_30[33];
	char truck_id[33];				// 180			truck_id
	char order_id[33];				// 181			order_id
	char user_defined_33[33];
	char user_defined_34[33];
	char user_defined_35[33];
	char user_defined_36[33];
	char user_defined_37[33];
	char user_defined_38[33];
	char user_defined_39[33];
	char user_defined_40[33];
	char user_defined_41[33];
	char user_defined_42[33];
	char user_defined_43[33];
	char user_defined_44[33];
	char user_defined_45[33];		// 194			nCopy
	char user_defined_46[33];		// 195
	char user_defined_47[33];		// 196
	char user_defined_48[33];		// 197
	char user_defined_49[33];
	char user_defined_50[33];		// 199
	
	char del_inst_4[33];			// 224
	char del_inst_5[33];			// 225
	char del_inst_6[33];			// 226
	char heat_charge_prt[25];		// 227
	double heat_charge_amt;			// 228
	double grand_total;				// 229
	double prev_total;				// 230
	
	double max_water_yard;			// 231
	double max_water_load;
	double sand_water_yard;
	double sand_water_load;
	double plant_water_yard;
	double plant_water_load;
	double allowed_water_yard;
	double allowed_water_load;
	char ticket_misc_1[9];
	char ticket_misc_2[9];			// 240
	
	char order_misc_1[9];			// 241
	char order_misc_2[9];			// 242
	char order_misc_3[9];			// 243
	char mix_class[3];				// 244
	char mix_strength[8];			// 245
	char mix_agg_size[6];			// 246
	char sales_type_code[3];		// 247
	char sales_type_short_desc[9];	// 248
	char sales_type_long_desc[33];	// 249

	TICKET_PRODUCT  prods[12];
} TICKET_REC;

// LOG ------------------------------------------------------------------------
typedef enum		
{ S_IDLE
, S_NEXT			// 1
, S_READY			// 2
, S_SAFE			// 3
, S_DROP			// 4
, S_SETTLE			// 5
, S_ADD_WAIT		// 6	
, S_ADD				// 7
, S_ASETTLE			// 8
, S_DISCH_WAIT		// 9
, S_DISCH			// 10
, S_DSETTLE			// 11
, S_HOLD_SETTLE		// 12
, S_HOLD_DROP		// 13
, S_HOLD_DISCH		// 14
, S_ABORT			// 15
, S_UPDATE			// 16
, S_HORN			// 17
, S_HOLD_ASETTLE	// 18
, S_SETTLE_PLC		// 19
, S_HOLD			// 20
, S_DELAY_PLC		// 21
, S_HOLD_ADD		// 22
//, S_HOLD_ADD
} STATE;

typedef enum
{ S_NONE				// 0
, S_NEW					// 1
, S_OK1					// 2
, S_VOIDED   			// 3
, S_ABORTED				// 4
, S_PRINTED 			// 5
, S_EXPORTED			// 6
} LOG_STATUS;

typedef enum
{ C_READ
, C_APPEND
, C_UPDATE
//, C_CANCEL
} LOG_CMD;

typedef enum
{ A_NOT
, A_TARGET
, A_LOAD
, A_VOID
} STOP;

typedef struct 
{
	long long tTimeSent;
	long long tTimeDone;
	int   nLogIdxX;				// not needed

	TICKET_REC sT;

	int    nSilo;				// 153
	int    nDrops;				// 154
	double fTruckTare;			// 155
	double fTax;				// 156
	bool   bPrintTarget;		// 157
	int	   nCopy;				// 194 User Defined #45	//DC 4.0.3

	double fLoad;
	double fGross;
	double fLoadTax;
	double fTotal;
	double fSpare;
	STATE eState;
	STOP   eStop;
	unsigned char  eJobStatus;
} LOG_REC;

///////////////////////////////////////////////////////////////////////////////
