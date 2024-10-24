#ifndef UTILITIES_DX9_H
#define UTILITIES_DX9_H

//#ifdef DX9_ENABLED

#include "servers/rendering/storage/utilities.h"
#include <d3d9.h>

namespace D3D9 {

class DX9RendererUtilities : public RendererUtilities {
public:
	DX9RendererUtilities();
	~DX9RendererUtilities();

	RS::InstanceType get_base_type(RID p_rid) const override;
	bool free(RID p_rid) override;

	void base_update_dependency(RID p_base, DependencyTracker *p_instance) override;

	RID visibility_notifier_allocate() override;
	void visibility_notifier_initialize(RID p_notifier) override;
	void visibility_notifier_free(RID p_notifier) override;

	void visibility_notifier_set_aabb(RID p_notifier, const AABB &p_aabb) override;
	void visibility_notifier_set_callbacks(RID p_notifier, const Callable &p_enter_callback, const Callable &p_exit_callback) override;

	AABB visibility_notifier_get_aabb(RID p_notifier) const override;
	void visibility_notifier_call(RID p_notifier, bool p_enter, bool p_deferred) override;

	void capture_timestamps_begin() override;
	void capture_timestamp(const String &p_name) override;
	uint32_t get_captured_timestamps_count() const override;
	uint64_t get_captured_timestamps_frame() const override;
	uint64_t get_captured_timestamp_gpu_time(uint32_t p_index) const override;
	uint64_t get_captured_timestamp_cpu_time(uint32_t p_index) const override;
	String get_captured_timestamp_name(uint32_t p_index) const override;

	void update_dirty_resources() override;
	void set_debug_generate_wireframes(bool p_generate) override;
	bool has_os_feature(const String &p_feature) const override;
	void update_memory_info() override;

	uint64_t get_rendering_info(RS::RenderingInfo p_info) override;
	String get_video_adapter_name() const override;
	String get_video_adapter_vendor() const override;
	RenderingDevice::DeviceType get_video_adapter_type() const override;
	String get_video_adapter_api_version() const override;

	Size2i get_maximum_viewport_size() const override;

private:
	LPDIRECT3D9 d3d; // Direct3D 9 对象
	LPDIRECT3DDEVICE9 d3dDevice; // Direct3D 设备
	// 其他 DirectX 9 相关成员变量
};
} //namespace D3D9
#endif // UTILITIES_DX9_H
