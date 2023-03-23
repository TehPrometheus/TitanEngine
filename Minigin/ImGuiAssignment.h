#pragma once
#include "Singleton.h"
#include <vector>
#include <chrono>
#include <list>
#include <numeric>
#include <type_traits>

struct Transform
{
	float matrix[16] =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
};

class GameObject3D
{
public:
	Transform transform{};
	int ID{};
};

class GameObject3DAlt
{
public:
	Transform* transform{};
	int ID{};
};

struct PlotData
{
	PlotData(float* xInput,float* yInput)
		:x(xInput), y(yInput){}
	~PlotData() { delete x; delete y; }

	PlotData(const PlotData& other) = delete;
	PlotData(PlotData&& other) = delete;
	PlotData& operator=(const PlotData& other) = delete;
	PlotData& operator=(PlotData&& other) = delete;

	float* x{nullptr};
	float* y{nullptr};
};

namespace dae
{
	class ImGuiAssignment final: public Singleton<ImGuiAssignment>
	{
	public:
		ImGuiAssignment();
		~ImGuiAssignment() override;

		ImGuiAssignment(const ImGuiAssignment& other) = delete;
		ImGuiAssignment(ImGuiAssignment&& other) = delete;
		ImGuiAssignment& operator=(const ImGuiAssignment& other) = delete;
		ImGuiAssignment& operator=(ImGuiAssignment&& other) = delete;

		void Exercise1();
		void Exercise2();

	private:
		bool m_ShowPlot1{ false };
		bool m_ShowPlot2{ false };
		bool m_ShowPlot3{ false };

		const static int NROFDATAPOINTS{ 11 };
		const int MAXSTEPSIZE{ static_cast<int>(powf(2.f,static_cast<float>(NROFDATAPOINTS) - 1)) };
		int m_Ex1SampleCount{10};
		int m_Ex2SampleCount{10};
		
		PlotData* m_Plot1{};
		PlotData* m_Plot2{};
		PlotData* m_Plot3{};

		void InitPlotData();
		static float GetMaxYValue(const float* yData);

		template <typename T>
		void CalculatePlotData()
		{
			long long elapsedTime{};
			std::list<long long> samples{};
			std::vector<T> largeVec(10'000'000);
			int dataPointNum{}; //Which data point are we accumulating data for?
			const int maxSampleCount{ m_Ex1SampleCount + 2 }; // +2 to account for top and bottom outlier

			for (int stepSize = 1; stepSize <= MAXSTEPSIZE; stepSize *= 2)
			{
				for (int sampleCount{ 0 }; sampleCount < maxSampleCount; ++sampleCount)
				{
					auto start = std::chrono::high_resolution_clock::now();
					for (size_t i{ 0 }; i < largeVec.size(); i += stepSize)
					{
						if constexpr(std::is_same_v<T, int>)
							largeVec[i] *= 2;
						else if constexpr(std::is_same_v<T,GameObject3D> || std::is_same_v<T,GameObject3DAlt>)
							largeVec[i].ID *= 2;
					}
					auto end = std::chrono::high_resolution_clock::now();
					elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
					samples.push_back(elapsedTime);
				}

				samples.sort();
				samples.pop_back();
				samples.pop_front();

				if(std::is_same_v<T,int>)
					m_Plot1->y[dataPointNum] = static_cast<float>(std::accumulate(samples.begin(), samples.end(), static_cast<long long>(0)) / static_cast<long long>(samples.size()));
				else if(std::is_same_v<T,GameObject3D>)
					m_Plot2->y[dataPointNum] = static_cast<float>(std::accumulate(samples.begin(), samples.end(), static_cast<long long>(0)) / static_cast<long long>(samples.size()));
				else if(std::is_same_v<T,GameObject3DAlt>)
					m_Plot3->y[dataPointNum] = static_cast<float>(std::accumulate(samples.begin(), samples.end(), static_cast<long long>(0)) / static_cast<long long>(samples.size()));


				samples.clear();
				++dataPointNum;
			}
		}

	};


}

