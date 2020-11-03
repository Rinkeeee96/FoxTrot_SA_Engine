#include "pch.h"
#include "CppUnitTest.h"

#include "Events/AppTickEvent60.h"
#include "ParticleSystem/ParticleEngine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{
	TEST_CLASS(ParticleEngineTests)
	{
	public:
		Object* obj = new Object(1);
		TEST_METHOD(TestMethod1)
		{
			obj->setName("test1");
			Assert::AreEqual(1, 1);
		}

		TEST_METHOD(ParticleIsSpawnedAtValidPosition)
		{
			// arrange
			ParticleAdapter particle(1);
			// act
			particle.setPosition(0, 1);
			// assert
			Assert::AreEqual(particle.getPositionX(), 0.f);
			Assert::AreEqual(particle.getPositionY(), 1.f);
		}


		TEST_METHOD(ObjectBaseClassPositionIsIgnored)
		{
			// arrange
			ParticleAdapter particle(1);
			// particle position
			particle.setPosition(2, 4);
			// object base class position
			particle.setPositionX(0);
			particle.setPositionY(1);

			// assert
			Assert::AreEqual(particle.getPositionX(), 2.f);
			Assert::AreEqual(particle.getPositionY(), 4.f);
		}

		TEST_METHOD(ParticleCountIsOverridable)
		{
			// arrange
			unsigned int fireDefaultCount = 250;
			ParticleAdapter particle(1);        
			particle.setPosition(800, 384);
			particle.setStyle(ParticleInit::ParticleStyle::FIRE);
			// act
			particle.initWithTotalParticles(5);
			// assert
			unsigned int count = 5;
			Assert::AreNotEqual(fireDefaultCount, particle.getParticleCount());
			Assert::AreEqual(particle.getParticleCount(), count);
		}

		TEST_METHOD(ParticleIsStopedWhenStyleIsNONE)
		{
			// arrange
			ParticleAdapter particle(1);
			// act
			particle.setStyle(ParticleInit::ParticleStyle::NONE);
			// assert
			// todo ????
		}

		TEST_METHOD(ParticlesAreUpdated)
		{
			// arrange
			ParticleAdapter particle1(1);
			particle1.setStyle(ParticleInit::ParticleStyle::RAIN);
			particle1.initWithTotalParticles(5);

			ParticleAdapter particle2(2);
			particle2.setStyle(ParticleInit::ParticleStyle::SMOKE);
			particle2.initWithTotalParticles(5);
			// copy the particle data vectors
			auto particle2VectorBeforeRun = particle2.getParticleDataVector();
			auto particle1VectorBeforeRun = particle1.getParticleDataVector();

			ParticleEngine engine;
			AppTickEvent60 tickEvent;

			// act
			// create a reference to the modifiable data vectors that are modified in the onUpdate
			auto& particle1VectorToBeModified = particle1.getParticleDataVector();
			auto& particle2VectorToBeModified = particle2.getParticleDataVector();
			engine.onUpdate(tickEvent);

			// assert
			//Assert::AreNotEqual(particle1VectorBeforeRun, particle1VectorToBeModified);
			//Assert::AreNotEqual(particle2VectorBeforeRun, particle2VectorToBeModified);
		}
	};
}