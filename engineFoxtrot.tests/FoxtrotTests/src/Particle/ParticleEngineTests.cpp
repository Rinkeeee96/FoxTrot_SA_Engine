#include "pch.h"
#include "CppUnitTest.h"

#include <CppUnitTestAssert.h>
#include <Engine/ParticleSystem/ParticleAdapter.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{
	TEST_CLASS(ParticleEngineTests)
	{
	public:
		TEST_METHOD(ParticleIsSpawnedAtValidPosition)
		{
			// arrange
			ParticleAdapter particle(1);
			// act
			particle.setPositionX(0);
			particle.setPositionY(1);
			// assert
			Assert::AreEqual(particle.getPositionX(), 0.0f);
			Assert::AreEqual(particle.getPositionY(), 1.0f);
		}


		TEST_METHOD(ObjectBaseClassPositionIsIgnored)
		{
			// arrange
			ParticleAdapter particle(1);
			// particle position
			particle.setPositionX(2);
			particle.setPositionY(4);
			// object base class position
			particle.setPositionX(0);
			particle.setPositionY(1);

			// assert
			Assert::AreNotEqual(particle.getPositionX(), 2.f);
			Assert::AreNotEqual(particle.getPositionY(), 4.f);
		}
	};
}