#include <cmath>
#include <cstdlib>
#ifndef NATIVE_SYSTEMC
#include "stratus_hls.h"
#endif

#include "SobelFilter.h"

SobelFilter::SobelFilter( sc_module_name n ): sc_module( n )
{
#ifndef NATIVE_SYSTEMC
	HLS_MAP_TO_REG_BANK(red);
	HLS_MAP_TO_REG_BANK(green);
	HLS_MAP_TO_REG_BANK(blue);
#endif
	SC_THREAD( do_filter );
	sensitive << i_clk.pos();
	dont_initialize();
	reset_signal_is(i_rst, false);
        
#ifndef NATIVE_SYSTEMC
	i_rgb.clk_rst(i_clk, i_rst);
  o_result.clk_rst(i_clk, i_rst);
#endif
}

SobelFilter::~SobelFilter() {}

// sobel mask
const int mask[MASK_N][MASK_X][MASK_Y] =  {{{1, 2, 1}, {2, 4, 2}, {1, 2, 1}}};

void SobelFilter::do_filter() {
	{
#ifndef NATIVE_SYSTEMC
		HLS_DEFINE_PROTOCOL("main_reset");
		i_rgb.reset();
		o_result.reset();
#endif
		wait();
	}
	row_sent = 0;
	while (true) {
		row_sent++;

		sc_dt::sc_uint<24> rgb;
		// Read and save data row by row
		for (int i = 0; i < (IMAGE_WIDTH + 2); i++){
#ifndef NATIVE_SYSTEMC
			HLS_PIPELINE_LOOP(SOFT_STALL, 1, "Read_Loop" ); 
#endif
#ifndef NATIVE_SYSTEMC
			{
				HLS_DEFINE_PROTOCOL("input");
				rgb = i_rgb.get();
				wait();
			}
#else
		rgb = i_rgb.read();
#endif
			{
#ifndef NATIVE_SYSTEMC
			HLS_CONSTRAIN_LATENCY(0, 3, "lat03");
#endif
				red[(row_sent-1)%3][i] = rgb.range(7,0);
				green[(row_sent-1)%3][i] = rgb.range(15,8);
				blue[(row_sent-1)%3][i] =  rgb.range(23,16);
			}
		}

		if (row_sent<3)
		continue;
		sc_dt::sc_uint<12> R, G, B;
		sc_dt::sc_uint<24> total;
		for (int w = 1; w < IMAGE_WIDTH+1; w++){
			{
				#ifndef NATIVE_SYSTEMC
					HLS_CONSTRAIN_LATENCY(0, 3, "lat02");
				#endif
				R = 0;
				G = 0;
				B = 0;
			}
			for (unsigned int v = 0; v < MASK_Y; ++v) {
#ifndef NATIVE_SYSTEMC
				HLS_PIPELINE_LOOP(SOFT_STALL, 1,"add_loop" ); 
#endif
				for (unsigned int u = 0; u < MASK_X; ++u) {
#ifndef NATIVE_SYSTEMC
						HLS_COALESCE_LOOP( CONSERVATIVE );
						HLS_CONSTRAIN_LATENCY(0, 3, "lat02");
#endif
					R += red[(row_sent-(MASK_Y-v))%3][w + (u-1)] * mask[1][u][v];
					G += green[(row_sent-(MASK_Y-v))%3][w + (u-1)] * mask[1][u][v];
					B += blue[(row_sent-(MASK_Y-v))%3][w + (u-1)] * mask[1][u][v];
				
				}
			} 

			{
#ifndef NATIVE_SYSTEMC
			HLS_CONSTRAIN_LATENCY(0, 3, "lat02");
#endif
			total.range(7,0) = R/MULT_FACTOR;
			total.range(15,8) = G/MULT_FACTOR;
			total.range(23,16) = B/MULT_FACTOR;  
			}

#ifndef NATIVE_SYSTEMC
			{
				HLS_DEFINE_PROTOCOL("output");
				o_result.put(total);
				wait();
			}
#else
			o_result.write(total);
#endif
		}
	}
}
