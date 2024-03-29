/*
 * Copyright (c) 2013-2015, The Linux Foundation. All rights reserved.
 * Not a contribution.
 *
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AUDIO_PLATFORM_API_H
#define AUDIO_PLATFORM_API_H
#include <sound/voice_params.h>

#define CODEC_BACKEND_DEFAULT_BIT_WIDTH 16
#define CODEC_BACKEND_DEFAULT_SAMPLE_RATE 48000

void *platform_init(struct audio_device *adev);
void platform_deinit(void *platform);
const char *platform_get_snd_device_name(snd_device_t snd_device);
int platform_get_snd_device_name_extn(void *platform, snd_device_t snd_device,
                                      char *device_name);
void platform_add_backend_name(char *mixer_path, snd_device_t snd_device);
int platform_get_pcm_device_id(audio_usecase_t usecase, int device_type);
int platform_get_snd_device_index(char *snd_device_index_name);
int platform_set_fluence_type(void *platform, char *value);
int platform_get_fluence_type(void *platform, char *value, uint32_t len);
int platform_set_snd_device_acdb_id(snd_device_t snd_device, unsigned int acdb_id);
int platform_get_snd_device_acdb_id(snd_device_t snd_device);
int platform_set_snd_device_bit_width(snd_device_t snd_device, unsigned int bit_width);
int platform_get_snd_device_bit_width(snd_device_t snd_device);
int platform_send_audio_calibration(void *platform, struct audio_usecase *usecase,
                                    int app_type, int sample_rate);
int platform_get_default_app_type(void *platform);
int platform_switch_voice_call_device_pre(void *platform);
int platform_switch_voice_call_enable_device_config(void *platform,
                                                    snd_device_t out_snd_device,
                                                    snd_device_t in_snd_device);
int platform_switch_voice_call_device_post(void *platform,
                                           snd_device_t out_snd_device,
                                           snd_device_t in_snd_device);
int platform_switch_voice_call_usecase_route_post(void *platform,
                                                  snd_device_t out_snd_device,
                                                  snd_device_t in_snd_device);
int platform_start_voice_call(void *platform, uint32_t vsid);
int platform_stop_voice_call(void *platform, uint32_t vsid);
int platform_set_voice_volume(void *platform, int volume);
int platform_set_mic_mute(void *platform, bool state);
int platform_get_sample_rate(void *platform, uint32_t *rate);
int platform_set_device_mute(void *platform, bool state, char *dir);
snd_device_t platform_get_output_snd_device(void *platform, audio_devices_t devices);
snd_device_t platform_get_input_snd_device(void *platform, audio_devices_t out_device);
int platform_set_hdmi_channels(void *platform, int channel_count);
int platform_edid_get_max_channels(void *platform);
void platform_get_parameters(void *platform, struct str_parms *query,
                             struct str_parms *reply);
int platform_set_parameters(void *platform, struct str_parms *parms);
int platform_set_incall_recording_session_id(void *platform, uint32_t session_id,
                                             int rec_mode);
int platform_stop_incall_recording_usecase(void *platform);
int platform_start_incall_music_usecase(void *platform);
int platform_stop_incall_music_usecase(void *platform);
int platform_update_lch(void *platform, struct voice_session *session,
                        enum voice_lch_mode lch_mode);
/* returns the latency for a usecase in Us */
int64_t platform_render_latency(audio_usecase_t usecase);
int platform_update_usecase_from_source(int source, audio_usecase_t usecase);

bool platform_listen_device_needs_event(snd_device_t snd_device);
bool platform_listen_usecase_needs_event(audio_usecase_t uc_id);

bool platform_sound_trigger_device_needs_event(snd_device_t snd_device);
bool platform_sound_trigger_usecase_needs_event(audio_usecase_t uc_id);

int platform_set_snd_device_backend(snd_device_t snd_device, const char * backend);

/* From platform_info_parser.c */
int platform_info_init(const char *filename);

struct audio_offload_info_t;
uint32_t platform_get_compress_offload_buffer_size(audio_offload_info_t* info);
uint32_t platform_get_pcm_offload_buffer_size(audio_offload_info_t* info);
uint32_t platform_get_compress_passthrough_buffer_size(audio_offload_info_t* info);

bool platform_check_and_set_codec_backend_cfg(struct audio_device* adev, struct audio_usecase *usecase);
int platform_get_usecase_index(const char * usecase);
int platform_set_usecase_pcm_id(audio_usecase_t usecase, int32_t type, int32_t pcm_id);
void platform_set_echo_reference(void *platform, bool enable);
void platform_get_device_to_be_id_map(int **be_id_map, int *length);

int platform_set_channel_allocation(void *platform, int channel_alloc);
int platform_get_edid_info(void *platform);
int platform_set_channel_map(void *platform, int ch_count, char *ch_map,
                             int snd_id);
int platform_set_stream_channel_map(void *platform, audio_channel_mask_t channel_mask, int snd_id);
int platform_set_edid_channels_configuration(void *platform, int channels);
unsigned char platform_map_to_edid_format(int format);
bool platform_is_edid_supported_format(void *platform, int format);
void platform_cache_edid(void * platform);
void platform_invalidate_edid(void * platform);
int platform_set_hdmi_config(struct stream_out *out);
int platform_set_device_params(struct stream_out *out, int param, int value);
int platform_set_audio_device_interface(const char * device_name, const char *intf_name,
                                        const char * codec_type);
int platform_set_spkr_device_tz_names(snd_device_t index,
                                       const char *spkr_1_tz_name, const char *spkr_2_tz_name);
const char *platform_get_spkr_1_tz_name(snd_device_t snd_device);
const char *platform_get_spkr_2_tz_name(snd_device_t snd_device);
#endif // AUDIO_PLATFORM_API_H
