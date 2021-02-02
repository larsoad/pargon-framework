#include "Pargon/Application.h"
#include "Pargon/Debugging.h"
#include "Pargon/Files.h"
#include "Pargon/Graphics.DirectX11.h"
#include "Pargon/Audio.XAudio2.h"
#include "Pargon/Input.Win32.h"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <csignal>

using namespace Pargon;

LONG Filter(_EXCEPTION_POINTERS* ExceptionInfo)
{
	printf("Filter");
	auto stack = Debugging::GetStackTrace();
	return EXCEPTION_CONTINUE_SEARCH;
}

void OnTerminate()
{
	std::exception_ptr eptr = std::current_exception();

	if (eptr)
	{
		try
		{
			std::rethrow_exception(eptr);
		}
		catch (const std::exception & e)
		{
			printf(e.what());
		}
		catch (...)
		{
			printf("unknown exception");
		}
	}
	else
	{
		printf("no exception");
	}

	auto stack = Debugging::GetStackTrace();
}

void OnSignal(int signal)
{
	printf("Signal %d\n\n", signal);
	auto stack = Debugging::GetStackTrace();

	std::quick_exit(EXIT_FAILURE);
}

class Playground : ApplicationInterface
{
public:
	Application Application;
	GraphicsDevice Graphics;
	AudioDevice Audio;
	KeyboardDevice Keyboard;

private:
	Geometry* _quad;
	Texture* _eagle;
	Material* _material;

	Mixer* _mixer;
	Sound* _sound;
	SoundInstance _instance;

	Vector2 _position = {};
	KeyboardState _state = {};

	struct Vertex
	{
		float X, Y;
		float U, V;
	};

public:
	void Run()
	{
		Pargon::Log("something {} {}", 1, 5);

		std::signal(SIGABRT, OnSignal);
		std::signal(SIGFPE, OnSignal);
		std::signal(SIGILL, OnSignal);
		std::signal(SIGINT, OnSignal);
		std::signal(SIGSEGV, OnSignal);
		std::signal(SIGTERM, OnSignal);


		std::set_terminate(OnTerminate);
		SetUnhandledExceptionFilter(Filter);

		WindowSettings settings = { "Playground"_s, WindowStyle::Resizable, 100, 100, 800, 600 };

		auto& info = Application.Initialize("Playground", *this);
		info.WriteInformation(Log);
		info.WriteCapabilities(Log);

		//std::abort(); // SIGABRT
		//std::terminate(); // SIGABRT and Terminate
		//throw std::exception("std::exception"); // (SIGABRT and Terminate) or Filter
		//int* n = nullptr; *n = 10; // SIGSEGV and Filter
		//CTRL + C // SIGINT
		//int denom = 0; int n = 10 / denom; // Filter

		Application.Run(settings);
	}

protected:
	void Setup() override
	{
		auto input = CreateWin32KeyboardInput();
		Keyboard.Setup(Application, std::move(input));

		auto renderer = CreateDirectX11Renderer();
		auto& info = Graphics.Setup(Application, std::move(renderer));
		info.WriteInformation(Log);
		info.WriteCapabilities(Log);

		auto soundFile = ApplicationDirectory().GetFile("Assets/Ambience.wav");
		auto eagleFile = ApplicationDirectory().GetFile("Assets/Eagle.png");

		_eagle = Graphics.CreateTexture(GraphicsStorage::TransferredToGpu);
		_eagle->Reset(eagleFile);
		_eagle->Unlock();

		_quad = Graphics.CreateGeometry(GraphicsStorage::TransferredToGpu);
		_quad->Unlock();

		_material = Graphics.CreateMaterial(GraphicsStorage::TransferredToGpu);
		_material->Reset("Assets/Material.hlsl");
		_material->SampleOptions.Add(BilinearSampling);
		_material->VertexLayout.Add({ ShaderElementType::Vector2, ShaderElementUsage::Position });
		_material->VertexLayout.Add({ ShaderElementType::Vector2, ShaderElementUsage::Coordinate });
		_material->Output.Add({ DisabledBlending, DisabledBlending });
		_material->Unlock();

		auto player = CreateXAudio2Player();
		Audio.Setup(std::move(player));

		_mixer = Audio.CreateMixer(2);
		_sound = Audio.CreateSound(*_mixer);

		auto soundData = soundFile.ReadData();

		_sound->SetData(std::move(soundData.Data));
		_instance = _sound->Play(nullptr);
	}

	void Process(Time elapsed) override
	{
		Keyboard.Update(_state);

		auto speed = 0.5f * (float)elapsed.InSeconds();

		if (_state.IsKeyDown(Key::Left)) _position.X -= speed;
		if (_state.IsKeyDown(Key::Right)) _position.X += speed;
		if (_state.IsKeyDown(Key::Down)) _position.Y -= speed;
		if (_state.IsKeyDown(Key::Up)) _position.Y += speed;

		_quad->Lock();
		_quad->Reset<Vertex>(GeometryTopology::TriangleStrip, {
			Vertex{ _position.X - 0.1f, _position.Y - 0.1f, 0.0f, 1.0f },
			Vertex{ _position.X - 0.1f, _position.Y + 0.1f, 0.0f, 0.0f },
			Vertex{ _position.X + 0.1f, _position.Y - 0.1f, 1.0f, 1.0f },
			Vertex{ _position.X + 0.1f, _position.Y + 0.1f, 1.0f, 0.0f }
		});
		_quad->Unlock();

		Graphics.SetColorTarget({}, 0);
		Graphics.SetDepthStencilTarget({});

		Graphics.ClearColorTarget(0.5f, 0.25f, 0.5f, 1.0f);

		Graphics.SetTexture(_eagle->Id(), 0);
		Graphics.SetVertexBuffer(_quad->Id(), sizeof(Vertex));
		Graphics.SetMaterial(_material->Id());
		Graphics.Draw(0, Graphics.DrawAll);

		Graphics.Render(GraphicsDevice::NoSynchronization);
	}

	void Shutdown() override
	{
		_instance.Stop();
		Audio.DestroySound(*_sound);
		Audio.DestroyMixer(*_mixer);

		Graphics.DestroyMaterial(_material->Id());
		Graphics.DestroyGeometry(_quad->Id());
		Graphics.DestroyTexture(_eagle->Id());
	}
};

auto CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) -> int
{
	Playground playground;
	playground.Run();
	return 0;
}
