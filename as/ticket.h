#pragma once
#include "stdafx.h"
#include <locale>

using namespace System;

namespace As
{
#define MSG_LEN    (8192)
#define MAX_TIC_FLD   288	// according to UL interface document
#define LOG   //

	typedef enum
	{ T_NONE				// ignore
	, T_TIME
	, T_TICKET				
	, T_VOID
	, T_BRES
	, T_EX_BRES
	, T_PURGE
	, T_INV
	, T_MAT
	, T_MIX
	, T_PLANT
	} TICKET_STATUS;

	typedef enum
	{D_NOT
	,D_CHAR		// 1
	,D_SHORT	// 2
	,D_LONG		// 3
	,D_DBL		// 4
	,D_STR		// 5
	} DTYPE;

	typedef struct
	{
		DTYPE type;
		short len;
		void  *ptr;
	} LINK_CTL;

	static TICKET_REC	sTic;

	//-const--------------------------------------------------------------------

	const LINK_CTL casLinkCtl[MAX_TIC_FLD] =
	{D_SHORT, 0, 							    &sTic.plant_num				// 001
	,D_LONG,  0,                                &sTic.ticket_num	        // 002
	,D_SHORT, 0,					 		    &sTic.truck_num				// 003
	,D_DBL,	  0,                                &sTic.load_size				// 004
	,D_STR,   sizeof(sTic.mix_code),            &sTic.mix_code	            // 005
	,D_STR,   sizeof(sTic.mix_desc),            &sTic.mix_desc         		// 006
	,D_DBL,   0,                                &sTic.slump					// 007
	,D_STR,   sizeof(sTic.use), 				&sTic.use  					// 008
	,D_STR,   sizeof(sTic.date),                &sTic.date					// 009

	,D_STR,   sizeof(sTic.customer_code),       &sTic.customer_code			// 010
	,D_STR,   sizeof(sTic.customer_name_1),     &sTic.customer_name_1		// 011
	,D_STR,   sizeof(sTic.customer_name_2),	    &sTic.customer_name_2   	// 012
	,D_STR,   sizeof(sTic.customer_name_3),  	&sTic.customer_name_3	    // 013 
	,D_LONG,  0,	     						&sTic.driver_num   			// 014 
	,D_STR,   sizeof(sTic.driver_name),         &sTic.driver_name			// 015
	,D_STR,   sizeof(sTic.del_addr_1),	    	&sTic.del_addr_1			// 016 
	,D_STR,   sizeof(sTic.del_addr_2),          &sTic.del_addr_2			// 017
	,D_STR,   sizeof(sTic.po_number),			&sTic.po_number  			// 018 
	,D_LONG,  0,                            	&sTic.order_num 			// 019 

	,D_DBL,   0,                                &sTic.quantity				// 020
	,D_STR,   sizeof(sTic.del_inst_1),		    &sTic.del_inst_1			// 021
	,D_STR,   sizeof(sTic.del_inst_2),		    &sTic.del_inst_2			// 022
	,D_STR,   sizeof(sTic.del_inst_3),		    &sTic.del_inst_3			// 023
	,D_SHORT, 0,								&sTic.tax_code				// 024
	,D_STR,   sizeof(sTic.time_due),            &sTic.time_due				// 025
	,D_STR,   sizeof(sTic.reserved),            &sTic.reserved				// 026
	,D_DBL,   0,								&sTic.cum_qty				// 027
	,D_DBL,   0,								&sTic.ordered_qty	 		// 028
	,D_STR,   sizeof(sTic.mix_prod_code),		&sTic.mix_prod_code			// 029

	,D_STR,   sizeof(sTic.mix_prod_desc),       &sTic.mix_prod_desc			// 030
	,D_STR,   sizeof(sTic.unit),                &sTic.unit					// 031
	,D_DBL,   0,                                &sTic.mix_price	   			// 032
	,D_DBL,   0,                                &sTic.mix_ext_amount		// 033

	,D_DBL,   0,                                &sTic.prods[0].load_qty		// 034
	,D_STR,   sizeof(sTic.prods[0].name),		&sTic.prods[0].name			// 035
	,D_STR,   sizeof(sTic.prods[0].desc),		&sTic.prods[0].desc			// 036
	,D_STR,   sizeof(sTic.prods[0].um),			&sTic.prods[0].um			// 037
	,D_DBL,   0,                                &sTic.prods[0].price		// 038
	,D_DBL,   0,                                &sTic.prods[0].amount		// 039

	,D_DBL,   0,                                &sTic.prods[1].load_qty		// 040
	,D_STR,   sizeof(sTic.prods[1].name),		&sTic.prods[1].name			// 041
	,D_STR,   sizeof(sTic.prods[1].desc),		&sTic.prods[1].desc			// 042
	,D_STR,   sizeof(sTic.prods[1].um),			&sTic.prods[1].um			// 043
	,D_DBL,   0,                                &sTic.prods[1].price		// 044
	,D_DBL,   0,                                &sTic.prods[1].amount		// 045

	,D_DBL,   0,                                &sTic.prods[2].load_qty		// 046
	,D_STR,   sizeof(sTic.prods[2].name),		&sTic.prods[2].name			// 047
	,D_STR,   sizeof(sTic.prods[2].desc),		&sTic.prods[2].desc			// 048
	,D_STR,   sizeof(sTic.prods[2].um),			&sTic.prods[2].um			// 049
	,D_DBL,   0,                                &sTic.prods[2].price		// 050
	,D_DBL,   0,                                &sTic.prods[2].amount		// 051

	,D_DBL,   0,                                &sTic.prods[3].load_qty		// 052
	,D_STR,   sizeof(sTic.prods[3].name),		&sTic.prods[3].name			// 053
	,D_STR,   sizeof(sTic.prods[3].desc),		&sTic.prods[3].desc			// 054
	,D_STR,   sizeof(sTic.prods[3].um),			&sTic.prods[3].um			// 055
	,D_DBL,   0,                                &sTic.prods[3].price		// 056
	,D_DBL,   0,                                &sTic.prods[3].amount		// 057

	,D_DBL,   0,                                &sTic.prods[4].load_qty		// 058
	,D_STR,   sizeof(sTic.prods[4].name),		&sTic.prods[4].name			// 059
	,D_STR,   sizeof(sTic.prods[4].desc),		&sTic.prods[4].desc			// 060
	,D_STR,   sizeof(sTic.prods[4].um),			&sTic.prods[4].um			// 061
	,D_DBL,   0,                                &sTic.prods[4].price		// 062
	,D_DBL,   0,                                &sTic.prods[4].amount		// 063

	,D_DBL,   0,                                &sTic.prods[5].load_qty		// 064
	,D_STR,   sizeof(sTic.prods[5].name),		&sTic.prods[5].name			// 065
	,D_STR,   sizeof(sTic.prods[5].desc),		&sTic.prods[5].desc			// 066
	,D_STR,   sizeof(sTic.prods[5].um),			&sTic.prods[5].um			// 067
	,D_DBL,   0,                                &sTic.prods[5].price		// 068
	,D_DBL,   0,                                &sTic.prods[5].amount		// 069

	,D_STR,   sizeof(sTic.min_load_charge_prt), &sTic.min_load_charge_prt	// 070
	,D_DBL,   0,                                &sTic.min_load_charge_amt	// 071
	,D_DBL,   0,                                &sTic.subtotal				// 072
	,D_DBL,   0,                                &sTic.tax_total				// 073
	,D_DBL,   0,                                &sTic.order_cum_total	    // 074
	,D_STR,   sizeof(sTic.time_sent),           &sTic.time_sent				// 075
	,D_STR,   sizeof(sTic.zone), 				&sTic.zone					// 076

	//project
	,D_STR,   sizeof(sTic.project_code),		&sTic.project_code		    // 077
	,D_STR,   sizeof(sTic.ordered_by),		    &sTic.ordered_by	 	    // 078 
	,D_STR,   sizeof(sTic.special_inst_1),		&sTic.special_inst_1		// 079 
	,D_STR,   sizeof(sTic.special_inst_2),		&sTic.special_inst_2		// 080
	,D_STR,   sizeof(sTic.operator_msg),		&sTic.operator_msg			// 081 
	,D_CHAR,  0,                                &sTic.local_ticket_change	// 082 
	,D_STR,   sizeof(sTic.lot_num),				&sTic.lot_num				// 083
	,D_STR,   sizeof(sTic.project_phone),		&sTic.project_phone			// 084 
	,D_STR,   sizeof(sTic.percent_calcium),     &sTic.percent_calcium	    // 085 
	,D_STR,   sizeof(sTic.percent_air_ent),	    &sTic.percent_air_ent		// 086
	,D_STR,   sizeof(sTic.super_plasticizer),   &sTic.super_plasticizer		// 087 

	,D_NOT,   0,                                 NULL						 // 088 blank
	,D_NOT,   0,                                 NULL						 // 089 blank
	,D_NOT,   0,                                 NULL						 // 090 blank
	,D_NOT,   0,                                 NULL						 // 091 blank

	,D_DBL,   0,                                 &sTic.num_percent_calcium	 // 092 minimum load charge amount
	,D_SHORT, 0,								 &sTic.num_percent_air	     // 093 calcium
	,D_SHORT, 0,								 &sTic.num_super_plasticizer // 094 air
	,D_SHORT, 0,								 &sTic.percent_hot_water	 // 095 plasticizer
	,D_SHORT, 0,								 &sTic.pounds_of_ice		 // 096 hot water

	,D_SHORT, 0,                                 &sTic.loads_delivered		 // 097 
	,D_STR,   sizeof(sTic.admix_code),  	     &sTic.admix_code			 // 098
	,D_STR,   sizeof(sTic.job_name),			 &sTic.job_name		    	 // 099
	,D_CHAR,  0,                                 &sTic.print_weights		 // 100

	,D_STR,   sizeof(sTic.mix_code_1),	    	 &sTic.mix_code_1 		     // 101
	,D_STR,   sizeof(sTic.mix_desc_1), 			 &sTic.mix_desc_1			 // 102
	,D_STR,   sizeof(sTic.agg_1_name), 			 &sTic.agg_1_name			 // 103
	,D_SHORT, 0,                                 &sTic.agg_1_weight          // 104
	,D_STR,   sizeof(sTic.agg_2_name), 			 &sTic.agg_2_name			 // 105
	,D_SHORT, 0,                                 &sTic.agg_2_weight          // 106
	,D_STR,   sizeof(sTic.agg_3_name), 			 &sTic.agg_3_name			 // 107
	,D_SHORT, 0,                                 &sTic.agg_3_weight          // 108
	,D_STR,   sizeof(sTic.agg_4_name), 			 &sTic.agg_4_name			 // 109
	,D_SHORT, 0,                                 &sTic.agg_4_weight          // 110
	,D_STR,   sizeof(sTic.cement_1_name), 		 &sTic.cement_1_name		 // 111
	,D_SHORT, 0,                                 &sTic.cement_1_weight       // 112
	,D_STR,   sizeof(sTic.cement_2_name), 		 &sTic.cement_2_name         // 113
	,D_SHORT, 0,                                 &sTic.cement_2_weight       // 114
	,D_STR,   sizeof(sTic.water_1_name), 		 &sTic.water_1_name          // 115
	,D_DBL,   0,                                 &sTic.water_1_weight        // 116

	,D_STR,   sizeof(sTic.admix_1_name), 		 &sTic.admix_1_name          // 117
	,D_DBL,   0,                                 &sTic.admix_1_ozs           // 118
	,D_STR,   sizeof(sTic.admix_1_name), 		 &sTic.admix_2_name          // 119
	,D_DBL,   0,                                 &sTic.admix_2_ozs           // 120
	,D_STR,   sizeof(sTic.admix_1_name), 		 &sTic.admix_3_name          // 121
	,D_DBL,   0,                                 &sTic.admix_3_ozs           // 122
	,D_STR,   sizeof(sTic.admix_1_name), 		 &sTic.admix_4_name          // 123
	,D_DBL,   0,                                 &sTic.admix_4_ozs           // 124
	,D_STR,   sizeof(sTic.admix_1_name), 		 &sTic.admix_5_name          // 125
	,D_DBL,   0,                                 &sTic.admix_5_ozs           // 126
	,D_STR,   sizeof(sTic.admix_1_name), 		 &sTic.admix_6_name          // 127
	,D_DBL,   0,                                 &sTic.admix_6_ozs           // 128

	,D_STR,   sizeof(sTic.cement_3_name), 		 &sTic.cement_3_name         // 129
	,D_SHORT, 0,                                 &sTic.cement_3_weight       // 130
	,D_STR,   sizeof(sTic.water_2_name), 		 &sTic.water_2_name          // 131
	,D_DBL,   0,                                 &sTic.water_2_weight        // 132
	,D_SHORT, 0,                          	     &sTic.mixer_time			 // 133
	,D_DBL,   0,                                 &sTic.max_load_size	     // 134
	,D_STR,   sizeof(sTic.agg_5_name), 			 &sTic.agg_5_name			 // 135
	,D_SHORT, 0,                                 &sTic.agg_5_weight          // 136
	,D_DBL,   0,                                 &sTic.percent_air       	 // 137
	,D_DBL,   0,                                 &sTic.slump_target   		 // 138
	,D_DBL,   0,                                 &sTic.max_dry_load_size	 // 139
	,D_DBL,   0,                                 &sTic.max_async_load_size	 // 140

	,D_CHAR,  0,                                 &sTic.agg_moist_ref		 // 141
	,D_CHAR,  0,                                 &sTic.metric	     		 // 142

	,D_NOT,   0,                                 NULL						 // 143 reserved
	,D_NOT,   0,                                 NULL						 // 144 reserved
	,D_NOT,   0,                                 NULL						 // 145 reserved
	,D_NOT,   0,                                 NULL						 // 146 reserved
	,D_NOT,   0,                                 NULL						 // 147 reserved
	,D_NOT,   0,                                 NULL						 // 148 reserved
	,D_SHORT, 0,                                 &sTic.zone_travel			 // 149

	,D_STR,   sizeof(sTic.mix_desc_ex),          &sTic.mix_desc_ex		     // 150
	,D_STR,   sizeof(sTic.weighmaster_name),     &sTic.weighmaster_name		 // 151
	,D_STR,   sizeof(sTic.begin_unload_time),    &sTic.begin_unload_time	 // 152
	//
	// Next 47 fields are user defined fields 4 to 50.
	//
	,D_STR,   sizeof(sTic.user_defined_4),		&sTic.user_defined_4		// 153
	,D_STR,   sizeof(sTic.user_defined_5),		&sTic.user_defined_5		// 154
	,D_STR,   sizeof(sTic.user_defined_6),      &sTic.user_defined_6 		// 155
	,D_STR,   sizeof(sTic.user_defined_7),      &sTic.user_defined_7 		// 156
	,D_STR,   sizeof(sTic.user_defined_8),		&sTic.user_defined_8 		// 157
	,D_STR,   sizeof(sTic.user_defined_9),		&sTic.user_defined_9 		// 158
	,D_STR,   sizeof(sTic.user_defined_10),		&sTic.user_defined_10		// 159

	,D_STR,   sizeof(sTic.user_defined_11),		&sTic.user_defined_11		// 160
	,D_STR,   sizeof(sTic.user_defined_12),		&sTic.user_defined_12		// 161
	,D_STR,   sizeof(sTic.user_defined_13),		&sTic.user_defined_13		// 162
	,D_STR,   sizeof(sTic.user_defined_14),		&sTic.user_defined_14		// 163
	,D_STR,   sizeof(sTic.user_defined_15),		&sTic.user_defined_15		// 164
	,D_STR,   sizeof(sTic.user_defined_16),		&sTic.user_defined_16		// 165
	,D_STR,   sizeof(sTic.user_defined_17),		&sTic.user_defined_17 		// 166
	,D_STR,   sizeof(sTic.user_defined_18),		&sTic.user_defined_18 		// 167
	,D_STR,   sizeof(sTic.user_defined_19),		&sTic.user_defined_19		// 168
	,D_STR,   sizeof(sTic.user_defined_20),		&sTic.user_defined_20		// 169

	,D_STR,   sizeof(sTic.user_defined_21),		&sTic.user_defined_21		// 170
	,D_STR,   sizeof(sTic.user_defined_22),		&sTic.user_defined_22		// 171
	,D_STR,   sizeof(sTic.user_defined_23),		&sTic.user_defined_23		// 172
	,D_STR,   sizeof(sTic.user_defined_24),		&sTic.user_defined_24		// 173
	,D_STR,   sizeof(sTic.user_defined_25),		&sTic.user_defined_25		// 174
	,D_STR,   sizeof(sTic.user_defined_26),		&sTic.user_defined_26 		// 175
	,D_STR,   sizeof(sTic.user_defined_27),		&sTic.user_defined_27 		// 176
	,D_STR,   sizeof(sTic.user_defined_28),		&sTic.user_defined_28 		// 177
	,D_STR,   sizeof(sTic.user_defined_29),		&sTic.user_defined_29		// 178
	,D_STR,   sizeof(sTic.user_defined_30),		&sTic.user_defined_30		// 179

	,D_STR,   sizeof(sTic.truck_id),			&sTic.truck_id				// 180
	,D_STR,   sizeof(sTic.order_id),			&sTic.order_id				// 181
	,D_STR,   sizeof(sTic.user_defined_33),		&sTic.user_defined_33		// 182
	,D_STR,   sizeof(sTic.user_defined_34),		&sTic.user_defined_34		// 183
	,D_STR,   sizeof(sTic.user_defined_35),		&sTic.user_defined_35		// 184
	,D_STR,   sizeof(sTic.user_defined_36),		&sTic.user_defined_36		// 185
	,D_STR,   sizeof(sTic.user_defined_37),		&sTic.user_defined_37		// 186
	,D_STR,   sizeof(sTic.user_defined_38),		&sTic.user_defined_38		// 187
	,D_STR,   sizeof(sTic.user_defined_39),		&sTic.user_defined_39		// 188
	,D_STR,   sizeof(sTic.user_defined_40),		&sTic.user_defined_40		// 189

	,D_STR,   sizeof(sTic.user_defined_41),		&sTic.user_defined_41		// 190
	,D_STR,   sizeof(sTic.user_defined_42),		&sTic.user_defined_42		// 191
	,D_STR,   sizeof(sTic.user_defined_43),		&sTic.user_defined_43		// 192
	,D_STR,   sizeof(sTic.user_defined_44),		&sTic.user_defined_44		// 193
	,D_STR,   sizeof(sTic.user_defined_45),		&sTic.user_defined_45		// 194
	,D_STR,   sizeof(sTic.user_defined_46),		&sTic.user_defined_46		// 195
	,D_STR,   sizeof(sTic.user_defined_47),		&sTic.user_defined_47		// 196
	,D_STR,   sizeof(sTic.user_defined_48),		&sTic.user_defined_48 		// 197
	,D_STR,   sizeof(sTic.user_defined_49),		&sTic.user_defined_49		// 198
	,D_STR,   sizeof(sTic.user_defined_50),		&sTic.user_defined_50		// 199

	,D_DBL,   0,                                &sTic.prods[0].order_qty	// 200
	,D_DBL,   0,                                &sTic.prods[0].cum_qty		// 201
	,D_STR,   sizeof(sTic.prods[0].long_desc),  &sTic.prods[0].long_desc	// 202
	,D_STR,   sizeof(sTic.prods[0].price),		&sTic.prods[0].price		// 203

	,D_DBL,	  0,                                &sTic.prods[1].order_qty	// 204
	,D_DBL,   0,                                &sTic.prods[1].cum_qty		// 205
	,D_STR,   sizeof(sTic.prods[1].long_desc),  &sTic.prods[1].long_desc	// 206
	,D_STR,   sizeof(sTic.prods[1].price),		&sTic.prods[1].price		// 207

	,D_DBL,   0,                                &sTic.prods[2].order_qty	// 208
	,D_DBL,   0,                                &sTic.prods[2].cum_qty 		// 209
	,D_STR,   sizeof(sTic.prods[2].long_desc),  &sTic.prods[2].long_desc	// 210
	,D_STR,   sizeof(sTic.prods[2].price),		&sTic.prods[2].price		// 211

	,D_DBL,   0,                                &sTic.prods[3].order_qty	// 212
	,D_DBL,   0,                                &sTic.prods[3].cum_qty  	// 213
	,D_STR,   sizeof(sTic.prods[3].long_desc),  &sTic.prods[3].long_desc	// 214
	,D_STR,   sizeof(sTic.prods[3].price),		&sTic.prods[3].price		// 215

	,D_DBL,   0,                                &sTic.prods[4].order_qty	// 216
	,D_DBL,   0,                                &sTic.prods[4].cum_qty  	// 217
	,D_STR,   sizeof(sTic.prods[4].long_desc),  &sTic.prods[4].long_desc	// 218
	,D_STR,   sizeof(sTic.prods[4].price),		&sTic.prods[4].price		// 219

	,D_DBL,   0,                                &sTic.prods[5].order_qty	// 220
	,D_DBL,   0,                                &sTic.prods[5].cum_qty  	// 221
	,D_STR,   sizeof(sTic.prods[5].long_desc),  &sTic.prods[5].long_desc	// 222
	,D_STR,   sizeof(sTic.prods[5].price),		&sTic.prods[5].price		// 223

	,D_STR,   sizeof(sTic.del_inst_4),			&sTic.del_inst_4			// 224
	,D_STR,   sizeof(sTic.del_inst_5),			&sTic.del_inst_5			// 225
	,D_STR,   sizeof(sTic.del_inst_6),			&sTic.del_inst_6			// 226
	,D_STR,   sizeof(sTic.heat_charge_prt),		&sTic.heat_charge_prt		// 227
	,D_DBL,   0,                                &sTic.heat_charge_amt		// 228
	,D_DBL,   0,                                &sTic.grand_total			// 229
	,D_DBL,   0,                                &sTic.prev_total			// 230

	,D_DBL,   0,                                &sTic.max_water_yard		// 231
	,D_DBL,   0,                                &sTic.max_water_load		// 232 
	,D_DBL,   0,                                &sTic.sand_water_yard		// 233 
	,D_DBL,   0,                                &sTic.sand_water_load		// 234 
	,D_DBL,   0,                                &sTic.plant_water_yard		// 235 
	,D_DBL,   0,                                &sTic.plant_water_load		// 236 
	,D_DBL,   0,                                &sTic.allowed_water_yard	// 237 
	,D_DBL,   0,                                &sTic.allowed_water_load	// 238 
	,D_STR,   sizeof(sTic.ticket_misc_1),       &sTic.ticket_misc_1			// 239 
	,D_STR,   sizeof(sTic.ticket_misc_2),		&sTic.ticket_misc_2			// 240 
	,D_STR,   sizeof(sTic.order_misc_1),		&sTic.order_misc_1			// 241
	,D_STR,   sizeof(sTic.order_misc_2),		&sTic.order_misc_2			// 242
	,D_STR,   sizeof(sTic.order_misc_3),		&sTic.order_misc_3			// 243 
	,D_STR,   sizeof(sTic.mix_class),			&sTic.mix_class				// 244 
	,D_STR,   sizeof(sTic.mix_strength),		&sTic.mix_strength			// 245 
	,D_STR,   sizeof(sTic.mix_agg_size),		&sTic.mix_agg_size			// 246 
	,D_STR,   sizeof(sTic.sales_type_code),		&sTic.sales_type_code		// 247 
	,D_STR,   sizeof(sTic.sales_type_short_desc),&sTic.sales_type_short_desc// 248 
	,D_STR,   sizeof(sTic.sales_type_long_desc),&sTic.sales_type_long_desc	// 249 

	,D_NOT,   0,                                NULL						// 250 reserved
	,D_NOT,   0,                                NULL						// 251 reserved
	,D_NOT,   0,                                NULL						// 252 reserved

	,D_DBL,   0,                                &sTic.prods[6].load_qty		// 253
	,D_STR,   sizeof(sTic.prods[6].name),		&sTic.prods[6].name			// 254
	,D_STR,   sizeof(sTic.prods[6].desc),		&sTic.prods[6].desc			// 255
	,D_STR,   sizeof(sTic.prods[6].um),			&sTic.prods[6].um			// 256
	,D_DBL,   0,                                &sTic.prods[6].price		// 257
	,D_DBL,   0,                                &sTic.prods[6].amount		// 258

	,D_DBL,   0,                                &sTic.prods[7].load_qty		// 259
	,D_STR,   sizeof(sTic.prods[7].name),		&sTic.prods[7].name			// 260
	,D_STR,   sizeof(sTic.prods[7].desc),		&sTic.prods[7].desc			// 261
	,D_STR,   sizeof(sTic.prods[7].um),			&sTic.prods[7].um			// 262
	,D_DBL,   0,                                &sTic.prods[7].price		// 263
	,D_DBL,   0,                                &sTic.prods[7].amount		// 264

	,D_DBL,   0,                                &sTic.prods[8].load_qty		// 265
	,D_STR,   sizeof(sTic.prods[8].name),		&sTic.prods[8].name			// 266
	,D_STR,   sizeof(sTic.prods[8].desc),		&sTic.prods[8].desc			// 267
	,D_STR,   sizeof(sTic.prods[8].um),			&sTic.prods[8].um			// 268
	,D_DBL,   0,                                &sTic.prods[8].price		// 269
	,D_DBL,   0,                                &sTic.prods[8].amount		// 270

	,D_DBL,   0,                                &sTic.prods[9].load_qty		// 271
	,D_STR,   sizeof(sTic.prods[9].name),		&sTic.prods[9].name			// 272
	,D_STR,   sizeof(sTic.prods[9].desc),		&sTic.prods[9].desc			// 273
	,D_STR,   sizeof(sTic.prods[9].um),			&sTic.prods[9].um			// 274
	,D_DBL,   0,                                &sTic.prods[9].price		// 275
	,D_DBL,   0,                                &sTic.prods[9].amount		// 276

	,D_DBL,   0,                                &sTic.prods[10].load_qty	// 277
	,D_STR,   sizeof(sTic.prods[10].name),		&sTic.prods[10].name		// 278
	,D_STR,   sizeof(sTic.prods[10].desc),		&sTic.prods[10].desc		// 279
	,D_STR,   sizeof(sTic.prods[10].um),		&sTic.prods[10].um			// 280
	,D_DBL,   0,                                &sTic.prods[10].price		// 281
	,D_DBL,   0,                                &sTic.prods[10].amount		// 282

	,D_DBL,   0,                                &sTic.prods[11].load_qty	// 283
	,D_STR,   sizeof(sTic.prods[11].name),		&sTic.prods[11].name		// 284
	,D_STR,   sizeof(sTic.prods[11].desc),		&sTic.prods[11].desc		// 285
	,D_STR,   sizeof(sTic.prods[11].um),		&sTic.prods[11].um			// 286
	,D_DBL,   0,                                &sTic.prods[11].price		// 287
	,D_DBL,   0,                                &sTic.prods[11].amount		// 288
	};

	//-class--------------------------------------------------------------------
	class CTicket  
	{
	public:
		CTicket()
		{
		}
		virtual ~CTicket()
		{
		}

	private:
		char		gacMsgRecv[MSG_LEN];
		char		*gpcMsgNbr;
		bool        bPlant;

		//-------------------------------------------------------------------------
	private:	
		void parseField(char *pFld, int nFldOfs)
		{
			int       nFldNum;
			char     *pcData, *pcTmp;
			LINK_CTL *psLinkCtl;
			//char      szMon[4];
			int       nIdx;

			LOG("as(parseField): Called.");

			nFldNum = (*pFld - '0') * 100 + (*(pFld+1) - '0') * 10 + *(pFld+2) - '0';
			nFldNum += nFldOfs;
			pcData = pFld + 3;

			if((nFldNum >= 0) && (nFldNum <= MAX_TIC_FLD))
				psLinkCtl = (LINK_CTL *)&casLinkCtl[nFldNum -1];
			else
			{
				LOG("as: ERROR in field %d '%s'", nFldNum, pcData);
				return;
			}

			//	if(nFldNum == 7)
			//		bSlump = true;
			//	else if(nFldNum == 138)
			//		bSlumpTarget = true;

			pcTmp = pcData;						// replace " characters
			while(*pcTmp)
			{
				if(*pcTmp == '"')
					*pcTmp = ' ';
				++pcTmp;
			}			

			nIdx = (int)strlen(pcData);				// remove trailing spaces
			while(nIdx && (pcData[nIdx-1] == ' '))
			{
				pcData[nIdx-1] = 0;	
				--nIdx;
			}

			switch(psLinkCtl->type)
			{
			case D_CHAR:
				*((char *)(psLinkCtl->ptr)) = *pcData; 

				LOG("field %d '%s'", nFldNum, pcData);
				break;

			case D_SHORT:
				*((short *)psLinkCtl->ptr) = atoi(pcData);

				LOG("field %d '%s'", nFldNum, pcData);
				break;

			case D_LONG:
				*((long *)psLinkCtl->ptr) = atol(pcData);

				LOG("field %d '%s'", nFldNum, pcData);
				break;

			case D_DBL:
				*((double *)psLinkCtl->ptr) = atof(pcData);

				LOG("field %d '%s'", nFldNum, pcData);
				break;

			case D_STR:
				// take out leading spaces on strings, don't run off of end
				nIdx = (int)strlen(pcData);				// remove leading spaces
				while(nIdx && isspace(*pcData))
				{
					++pcData;
					nIdx--;
				}
				if(!nIdx)
				{
					LOG("field %d                    IS EMPTY", nFldNum);
					return;
				}

				strncpy((char *)psLinkCtl->ptr, pcData, psLinkCtl->len);

				LOG("field %d '%s'", nFldNum, pcData);
				break;

			default:
				LOG("field %d '%s'       NOT-SUPPORTED", nFldNum, pcData);
				break;
			}
			return;
		}

		//-------------------------------------------------------------------------
		bool parseTicket(char **ppcTokNext)
		{
			char *pcTok, *psTicEnd = NULL;
			bool  bRet = false;

			LOG("as(parseTicket)\n");

			while(pcTok = strtok_s(NULL, "\r", ppcTokNext))
				//	while(pcTok = strtok(NULL, "\r"))
			{
				if(*pcTok == 'T')
				{
					LOG("as:  tic token %s.\n", pcTok);

					if(!strncmp(pcTok, "T003", 4))
						psTicEnd = pcTok + 4;
					else
						if(!strncmp(pcTok, "T007", 4))
							parseField(pcTok + 4, 0);
						else
							LOG("as:  Unknown ticket token %s.\n", pcTok);
				}
				else if(strlen(pcTok) > 3)
					parseField(pcTok, 0);
			}

			if(!psTicEnd)
				LOG("as:  Missing end token T003.\n");
			else
				if(!strcmp(gpcMsgNbr, psTicEnd))
				{
					LOG("as:  ticket %s OK.\n",  gpcMsgNbr);
					bRet = true;
				}
				else
					LOG("as:  Mismatched tokens T002 and T003.\n");

			return(bRet);
		}

		//-------------------------------------------------------------------------
		TICKET_STATUS parseBuffer(char *pcMsg, INI *psIni)
		{
			char *pcTok, *pcTokNext;


			LOG("as: parseBuffer()\n");
			memset(&sTic, 0, sizeof(sTic));

			pcTok = strtok_s(pcMsg, "\r", &pcTokNext);
			gpcMsgNbr = "NONE";

			if(!strncmp(pcTok, "T006", 4))					// cancel
			{
				gpcMsgNbr = pcTok + 4;
				sTic.ticket_num = atol(gpcMsgNbr);
				return T_VOID; 
			}
			else if(!strncmp(pcTok, "T002", 4))				// ticket begin
			{
				gpcMsgNbr = pcTok + 4;
				sTic.ticket_num = atol(gpcMsgNbr);

				if(parseTicket(&pcTokNext)
				&& ((sTic.plant_num == psIni->nPlantNum1) || (sTic.plant_num == psIni->nPlantNum2))
				)
					return T_TICKET;					// product name err
				else
					return T_NONE;						// ignore		
			}
			else if(!strncmp(pcTok, "T009", 4))					// brief response
			{
				return T_BRES;
			}
			else if(!strncmp(pcTok, "T013", 4))					// extended response
			{
				return T_EX_BRES;
			}
			else if(!strncmp(pcTok, "W001", 4))			// time
			{
				return T_TIME;								
			}
			return(T_NONE);
		}

		//---------------------------------------------------------------------------
	public:
		TICKET_STATUS processTicket(cli::array<Byte>^data, int len, LOG_REC *psLog, INI *psIni)
		{
			int nIdx;
			TICKET_STATUS cStatus;

			LOG("as:  processTicket(%d)\n", len);
			memset(psLog, 0, sizeof(LOG_REC));
			memset(&sTic, 0, sizeof(TICKET_REC));

			// strip frame formatting characters
			for(nIdx = 3; nIdx < len-2; nIdx++)
			{
				gacMsgRecv[nIdx-3] = data[nIdx];
			}
			gacMsgRecv[len-2] = 0;

///			if(pAll->eAsType != A_PROD)
//			{
//				bPlant = !bPlant;
//				sTic.plant_num = bPlant ? 99 : 55;
//			}
			cStatus = parseBuffer(gacMsgRecv, psIni);

			if(cStatus == T_TICKET)
			{
				psLog->sT = sTic;

				psLog->nSilo = atoi(sTic.user_defined_4);
				psLog->nDrops = atoi(sTic.user_defined_5);
				psLog->fTruckTare = atof(sTic.user_defined_6);
				psLog->fTax = atof(sTic.user_defined_7);
				psLog->nCopy = (int)atof(sTic.user_defined_45);		//DC 4.0.3 pritn number of tickets

				psLog->sT.user_defined_46[0] = sTic.user_defined_4[0];	//DC 4.1.2  Lane
				psLog->sT.user_defined_47[0] = sTic.user_defined_4[1];	//DC 4.1.2  Silo



				// corrections
				psLog->fTruckTare *= 0.00050; 
				psLog->fTax /= 100.0;

				//if((psLog->nSilo < 1) || (psLog->nSilo > 13))		//DC 4.0.0
				//	psLog->nSilo = 1;

				if((psLog->nDrops < 1) || (psLog->nDrops > 4))
					psLog->nDrops = 4;
			}	
			else if(cStatus == T_VOID)
				psLog->sT = sTic;

			return cStatus;
		}
	//////////////////////////////////////////////////////////////////////////////
	};
}