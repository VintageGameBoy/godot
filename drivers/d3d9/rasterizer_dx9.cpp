//

//#include "core/os/os.h"
#include "servers/display_server.h"
#include "rasterizer_dx9.h"



void RasterizerDX9::initialize() {
	Engine::get_singleton()->
		print_header(vformat("Directx 9 API %s - Compatibility - Using Device: %s - %s",
			RS::get_singleton()->get_video_adapter_api_version(),
			RS::get_singleton()->get_video_adapter_vendor(),
			RS::get_singleton()->get_video_adapter_name()));
	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.Windowed = TRUE; //窗口模式
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // 呈现完成后，可以丢弃缓冲区内容
	d3dpp.hDeviceWindow = (HWND)DisplayServer::get_singleton()->window_get_native_handle(DisplayServer::WINDOW_HANDLE, DisplayServer::MAIN_WINDOW_ID);
	HRESULT result = d3d->CreateDevice(
			D3DADAPTER_DEFAULT, //默认屏幕
			D3DDEVTYPE_HAL, //抽象层
			d3dpp.hDeviceWindow, //默认句柄
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, //软件顶点处理 硬件我不懂
			&d3dpp, //包含渲染设置的结构体
			&device); //输出参数，后续的所有渲染都依赖于此设备

	if (FAILED(result)) {
		// 处理设备创建失败的情况
		ERR_PRINT("Failed to create Direct3D device.");
		return;
	}
}



RasterizerDX9::RasterizerDX9() {
	// 创建 Direct3D 对象
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	// 下面初始化其他东西
}

RasterizerDX9::~RasterizerDX9() {
	if (device) {
		device->Release();
	}
	if (d3d) {
		d3d->Release();
	}
}
