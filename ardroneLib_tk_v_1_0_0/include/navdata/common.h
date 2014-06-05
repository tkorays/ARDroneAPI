#ifndef _TK_NAVDATA_COMMON_H_
#define _TK_NAVDATA_COMMON_H_

#define NAVDATA_HEADER 0X55667788
#define NAVDATA_MAX_SIZE 4096


#define NAVDATA_OPTION_DEMO(STRUCTURE,NAME,TAG)  TAG = 0,
#define NAVDATA_OPTION(STRUCTURE,NAME,TAG)       TAG ,
#define NAVDATA_OPTION_CKS(STRUCTURE,NAME,TAG)   NAVDATA_NUM_TAGS, TAG = 0xFFFF

typedef enum _navdata_tag_t {
	NAVDATA_OPTION_DEMO(navdata_demo_t, navdata_demo, NAVDATA_DEMO_TAG)

	NAVDATA_OPTION(navdata_time_t, navdata_time, NAVDATA_TIME_TAG)
	NAVDATA_OPTION(navdata_raw_measures_t, navdata_raw_measures, NAVDATA_RAW_MEASURES_TAG)
	NAVDATA_OPTION(navdata_phys_measures_t, navdata_phys_measures, NAVDATA_PHYS_MEASURES_TAG)
	NAVDATA_OPTION(navdata_gyros_offsets_t, navdata_gyros_offsets, NAVDATA_GYROS_OFFSETS_TAG)
	NAVDATA_OPTION(navdata_euler_angles_t, navdata_euler_angles, NAVDATA_EULER_ANGLES_TAG)
	NAVDATA_OPTION(navdata_references_t, navdata_references, NAVDATA_REFERENCES_TAG)
	NAVDATA_OPTION(navdata_trims_t, navdata_trims, NAVDATA_TRIMS_TAG)
	NAVDATA_OPTION(navdata_rc_references_t, navdata_rc_references, NAVDATA_RC_REFERENCES_TAG)
	NAVDATA_OPTION(navdata_pwm_t, navdata_pwm, NAVDATA_PWM_TAG)
	NAVDATA_OPTION(navdata_altitude_t, navdata_altitude, NAVDATA_ALTITUDE_TAG)
	NAVDATA_OPTION(navdata_vision_raw_t, navdata_vision_raw, NAVDATA_VISION_RAW_TAG)
	NAVDATA_OPTION(navdata_vision_of_t, navdata_vision_of, NAVDATA_VISION_OF_TAG)
	NAVDATA_OPTION(navdata_vision_t, navdata_vision, NAVDATA_VISION_TAG)
	NAVDATA_OPTION(navdata_vision_perf_t, navdata_vision_perf, NAVDATA_VISION_PERF_TAG)
	NAVDATA_OPTION(navdata_trackers_send_t, navdata_trackers_send, NAVDATA_TRACKERS_SEND_TAG)
	NAVDATA_OPTION(navdata_vision_detect_t, navdata_vision_detect, NAVDATA_VISION_DETECT_TAG)
	NAVDATA_OPTION(navdata_watchdog_t, navdata_watchdog, NAVDATA_WATCHDOG_TAG)
	NAVDATA_OPTION(navdata_adc_data_frame_t, navdata_adc_data_frame, NAVDATA_ADC_DATA_FRAME_TAG)
	NAVDATA_OPTION(navdata_video_stream_t, navdata_video_stream, NAVDATA_VIDEO_STREAM_TAG)
	NAVDATA_OPTION(navdata_games_t, navdata_games, NAVDATA_GAMES_TAG)
	NAVDATA_OPTION(navdata_pressure_raw_t, navdata_pressure_raw, NAVDATA_PRESSURE_RAW_TAG)
	NAVDATA_OPTION(navdata_magneto_t, navdata_magneto, NAVDATA_MAGNETO_TAG)
	NAVDATA_OPTION(navdata_wind_speed_t, navdata_wind_speed, NAVDATA_WIND_TAG)
	NAVDATA_OPTION(navdata_kalman_pressure_t, navdata_kalman_pressure, NAVDATA_KALMAN_PRESSURE_TAG)
	NAVDATA_OPTION(navdata_hdvideo_stream_t, navdata_hdvideo_stream, NAVDATA_HDVIDEO_STREAM_TAG)
	NAVDATA_OPTION(navdata_wifi_t, navdata_wifi, NAVDATA_WIFI_TAG)


	// TODO: maybe navdata_zimmu_3000 coult be integrated into an existing navdata like navdata_adc_data_frame_t or ...
	NAVDATA_OPTION(navdata_zimmu_3000_t, navdata_zimmu_3000, NAVDATA_ZIMMU_3000_TAG)

	NAVDATA_OPTION_CKS(navdata_cks_t, navdata_cks, NAVDATA_CKS_TAG)
} navdata_tag_t;



#define NAVDATA_OPTION_MASK(option) (1<<(option))
#define NAVDATA_OPTION_FULL_MASK ((1<<NAVDATA_NUM_TAGS)-1)

typedef struct _navdata_option_t {
	UINT16 tag;
	UINT16 size;
	UINT8 data[1];
} navdata_option_t;

typedef struct _navdata_t {
	UINT32 header;
	UINT32 ardrone_state;
	UINT32 sequence;
	bool vision_defined;
	navdata_option_t options[1];
} navdata_t;


typedef struct _navdata_demo_t {
	UINT16 tag;
	UINT16 size;
	UINT32 ctrl_state;
	UINT32 vbat_flying_precentage;

	FLOAT theta;
	FLOAT phi;
	FLOAT psi;

	INT32 altitude;

	FLOAT vx;
	FLOAT vy;
	FLOAT vz;

	UINT32 num_frames;

	// some deprecated optons

} navdata_demo_t;

typedef struct navdata_cks_t {
	UINT16 tag;
	UINT16 size;
	UINT32 cks;
} navdata_cks_t;

#endif // _TK_NAVDATA_COMMON_H_