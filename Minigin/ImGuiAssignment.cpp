#include "ImGuiAssignment.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <numeric>
#include "imgui/imgui.h"
#include "imgui/imgui_plot.h"
using namespace std::chrono;
using namespace std;

dae::ImGuiAssignment::ImGuiAssignment()
{
	InitPlotData();
}

dae::ImGuiAssignment::~ImGuiAssignment()
{
	delete m_Plot1;
}
void dae::ImGuiAssignment::Exercise1()
{
	static float maxYValue{};
	constexpr int minSampleCount{ 2 }, maxSampleCount{ 1000 };
	ImGui::Begin("Exercise 1",0, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::InputInt("# samples", &m_Ex1SampleCount);
	m_Ex1SampleCount = std::clamp(m_Ex1SampleCount, minSampleCount, maxSampleCount);

	if(ImGui::Button("Trash the cache"))
	{
		CalculatePlotData<int>();
		m_ShowPlot1 = true;
		maxYValue = GetMaxYValue(m_Plot1->y);
	}

	if(m_ShowPlot1)
	{
		//Int Plot
		ImGui::PlotConfig conf;
		conf.values.xs = m_Plot1->x;
		conf.values.ys = m_Plot1->y;
		conf.values.count = NROFDATAPOINTS;
		conf.values.color = ImGui::GetColorU32(ImVec4(1,0,0,1));
		conf.scale.min = 0;
		conf.scale.max = maxYValue;
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.frame_size = ImVec2(200, 100);
		conf.line_thickness = 2.f;
		
		ImGui::Plot("plot", conf);
	}

	ImGui::End();
}

void dae::ImGuiAssignment::Exercise2()
{
	static float maxYValue1{};
	static float maxYValue2{};
	constexpr int minSampleCount{ 2 }, maxSampleCount{ 1000 };
	ImGui::Begin("Exercise 2", 0, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::InputInt("# samples", &m_Ex2SampleCount);
	m_Ex2SampleCount = std::clamp(m_Ex2SampleCount, minSampleCount, maxSampleCount);

	if (ImGui::Button("Trash the cache with GameObject3D"))
	{
		CalculatePlotData<GameObject3D>();
		m_ShowPlot2 = true;
		maxYValue1 = GetMaxYValue(m_Plot2->y);
	}

	if (m_ShowPlot2)
	{
		//GameObjects Plot
		ImGui::PlotConfig conf;
		conf.values.xs = m_Plot2->x; 
		conf.values.ys = m_Plot2->y;
		conf.values.count = NROFDATAPOINTS;
		conf.values.color = ImGui::GetColorU32(ImVec4(0, 1, 0, 1));
		conf.scale.min = 0.f;
		conf.scale.max = maxYValue1;
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.frame_size = ImVec2(200, 100);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot", conf);
	}
	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
	{
		CalculatePlotData<GameObject3DAlt>();
		m_ShowPlot3 = true;
		maxYValue2 = GetMaxYValue(m_Plot3->y);
	}

	if (m_ShowPlot3)
	{
		static const float* combinedYData[] = { m_Plot2->y,m_Plot3->y };
		static ImU32 colors[2] = { ImGui::GetColorU32(ImVec4(0,1,0,1)),ImGui::GetColorU32(ImVec4(0,0,1,1)) };
		static uint32_t selectionStart = 0, selectionLength = 0;
		//GameObjectsAlt Plot
		ImGui::PlotConfig conf;
		conf.values.xs = m_Plot3->x; 
		conf.values.ys = m_Plot3->y;
		conf.values.count = NROFDATAPOINTS;
		conf.values.color = ImGui::GetColorU32(ImVec4(0, 0, 1, 1));
		conf.scale.min = 0.f;
		conf.scale.max = maxYValue2;
		conf.tooltip.show = true;
		conf.tooltip.format = "x=%.2f, y=%.2f";
		conf.frame_size = ImVec2(200, 100);
		conf.line_thickness = 2.f;

		ImGui::Plot("plot", conf);
		
		ImGui::Text("Combined:");
		//Combined Plot
		ImGui::PlotConfig conf2;
		conf2.values.xs = m_Plot3->x;
		conf2.values.count = NROFDATAPOINTS;
		conf2.values.ys_list = combinedYData;
		conf2.values.ys_count = 2;
		conf2.values.colors = colors;
		conf2.scale.min = 0.f;
		conf2.scale.max = maxYValue1 > maxYValue2 ? maxYValue1 : maxYValue2;
		conf2.tooltip.show = true;
		conf2.tooltip.format = "x=%.2f, y=%.2f";
		conf2.frame_size = ImVec2(200, 100);
		conf2.line_thickness = 2.f;

		ImGui::Plot("plot", conf2);
	}
	ImGui::End();
}


void dae::ImGuiAssignment::InitPlotData()
{
	m_Plot1 = new PlotData(new float[NROFDATAPOINTS], new float[NROFDATAPOINTS]);
	m_Plot2 = new PlotData(new float[NROFDATAPOINTS], new float[NROFDATAPOINTS]);
	m_Plot3 = new PlotData(new float[NROFDATAPOINTS], new float[NROFDATAPOINTS]);

	int idx{};
	for(int stepSize{1}; stepSize <= MAXSTEPSIZE ; stepSize *= 2)
	{
		m_Plot1->x[idx] = static_cast<float>(stepSize);
		m_Plot2->x[idx] = static_cast<float>(stepSize);
		m_Plot3->x[idx] = static_cast<float>(stepSize);
		++idx;
	}
}

float dae::ImGuiAssignment::GetMaxYValue(const float* yData)
{
	float max{};

	for(int i{}; i < NROFDATAPOINTS; ++i)
	{
		if(yData[i] > max)
			max = yData[i];
	}

	return max;
}
