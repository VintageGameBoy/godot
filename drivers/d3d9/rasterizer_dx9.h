#ifndef RASTERIZER_DX9_H
#define RASTERIZER_DX9_H

#include <d3d9.h>
#include "servers/rendering/renderer_compositor.h"
#include "storage/utilities.h"

class RasterizerDX9 : public RendererCompositor {
private:
	IDirect3D9 *d3d = nullptr;
	IDirect3DDevice9 *device = nullptr;

protected:
	D3D9::DX9RendererUtilities *utilities = nullptr;

public:

	/// <summary>
	/// 提供渲染过程中常用的实用工具，如矩阵运算、状态管理等 帮助简化渲染任务
	/// </summary>
	/// <returns></returns>
	RendererUtilities *get_utilities() { return utilities; }
	/// <summary>
	/// 管理光源的存储和操作，包括光源的创建、更新和销毁。支持对场景中所有光源的访问。
	/// </summary>
	/// <returns></returns>
	RendererLightStorage *get_light_storage() override;
	/// <summary>
	/// 管理材质的存储和操作，包括材质的创建、更新和销毁，确保渲染过程中的材质状态正
	/// </summary>
	/// <returns></returns>
	RendererMaterialStorage *get_material_storage() override;
	/// <summary>
	/// 管理网格（模型）的存储和操作，处理网格数据的创建、更新和渲染。
	/// </summary>
	/// <returns></returns>
	RendererMeshStorage *get_mesh_storage() override;
	/// <summary>
	/// 管理粒子系统的存储和操作，包括粒子的创建、更新和渲染，支持各种粒子效果。
	/// </summary>
	/// <returns></returns>
	RendererParticlesStorage *get_particles_storage() override;
	/// <summary>
	/// 管理纹理的存储和操作，包括纹理的创建、更新和销毁，确保渲染过程中的纹理状态正确。
	/// </summary>
	/// <returns></returns>
	RendererTextureStorage *get_texture_storage() override;
	/// <summary>
	/// 管理全局光照的计算和更新，处理场景中的光照效果，以提高渲染质量。
	/// </summary>
	/// <returns></returns>
	RendererGI *get_gi() override;
	/// <summary>
	/// 管理雾效的应用，包括雾的参数设置和效果实现，以增强场景的深度感和氛围。
	/// </summary>
	/// <returns></returns>
	RendererFog *get_fog() override;
	/// <summary>
	/// 管理画布渲染，处理 UI 元素和 2D 图形的绘制，确保 UI 和游戏世界的渲染正确。
	/// </summary>
	/// <returns></returns>
	RendererCanvasRender *get_canvas() override;
	/// <summary>
	/// 管理场景的渲染过程，协调场景中的各种元素（如网格、光源等）的渲染。
	/// </summary>
	/// <returns></returns>
	RendererSceneRender *get_scene() override;

	/// <summary>
	/// 返回当前渲染帧的编号（通常是从引擎启动后计算的帧数）。
	/// 供其他系统或功能（如动画、时间管理等）查询当前帧数。
	/// </summary>
	/// <returns></returns>
	uint64_t get_frame_number() const override;
	/// <summary>
	/// 返回上一帧与当前帧之间的时间差（以秒为单位）。
	/// 使开发者能够基于时间进行逻辑更新，例如物体移动、动画播放等。
	/// </summary>
	/// <returns></returns>
	double get_frame_delta_time() const override;
	/// <summary>
	/// 返回自引擎启动以来的总时间（以秒为单位）。
	/// 供其他系统查询总运行时间，适用于需要持续时间的效果或状态。
	/// </summary>
	/// <returns></returns>
	double get_total_time() const override;

	/// <summary>
	/// 在渲染器启动时执行一次性配置，准备渲染环境。
	/// </summary>
	void initialize() override;
	/// <summary>
	/// 在每帧开始时调用，传入当前帧的时间步长。
	/// </summary>
	/// <param name="frame_step"></param>
	void begin_frame(double frame_step) override;
	/// <summary>
	/// 将多个渲染目标（如后备缓冲区）复制到屏幕上。
	/// </summary>
	/// <param name="p_screen"></param>
	/// <param name="p_render_targets"></param>
	/// <param name="p_amount"></param>
	void blit_render_targets_to_screen(DisplayServer::WindowID p_screen, const BlitToScreen *p_render_targets, int p_amount) override;
	/// <summary>
	/// 在 OpenGL 渲染器中结束当前帧。
	/// </summary>
	/// <param name="p_swap_buffers"></param>
	void gl_end_frame(bool p_swap_buffers) override;
	/// <summary>
	/// 结束当前帧，可能涉及交换缓冲区。
	/// </summary>
	/// <param name="p_swap_buffers"></param>
	void end_frame(bool p_swap_buffers) override;
	/// <summary>
	/// 释放资源，清理渲染器。
	/// 在引擎关闭或渲染器不再使用时，执行清理工作，避免内存泄漏。
	/// </summary>
	void finalize() override;

	RasterizerDX9();
	~RasterizerDX9();
};

#endif // RASTERIZER_DX9_H
