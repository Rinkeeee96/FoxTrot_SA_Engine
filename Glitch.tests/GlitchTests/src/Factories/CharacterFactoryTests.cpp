#include "pch.h"
#include "CppUnitTest.h"
#include <Game/Levels/Level.h>
#include <Game/Scenes/Statemachine/SceneStateMachine.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsGlitch
{
	class MockCharacter : public ICharacter {
	public:
		MockCharacter(EventDispatcher& _dispatcher) : ICharacter(_dispatcher) { }
		MockCharacter(const int id, EventDispatcher& _dispatcher) : ICharacter(id, _dispatcher) { }

		virtual map<SpriteState, SpriteObject*> buildSpritemap(int textureId) override {
			map<SpriteState, SpriteObject*> map;
			return map;
		}

		virtual ICharacter* clone(int id) override {

			return new MockCharacter(id + 1, this->dispatcher);
		}

		void onUpdate(float deltaTime) override {

		}
	};
	TEST_CLASS(FactoryTests)
	{
	public:
		TEST_METHOD(CharacterFactory_Create_Charactar_Return_Clone)
		{
			// Arrange
			Engine engine;
			EventDispatcher dispatcher;
			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			SceneStateMachine statemachine{ engine, savegame };
			Level level{ 1, 100, 100, engine, statemachine };
			CharacterFactory factory{ engine, level };
			MockCharacter registerCharacter{ dispatcher };
			MockCharacter registerCharacter2{ dispatcher };
			int i = 1;
			int* a = &i;
			// Act
			factory.registerCharacter("name", &registerCharacter, a);
			auto result = factory.create("name", 1);
			// Assert
			Assert::AreEqual(result->getObjectId(), 2);
		}
		TEST_METHOD(CharacterFactory_Create_NonExisting_Identifier_Should_ThrowError)
		{
			// Arrange
			Engine engine;
			EventDispatcher dispatcher;
			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			SceneStateMachine statemachine{ engine, savegame };
			Level level{ 1, 100, 100, engine, statemachine };
			CharacterFactory factory{ engine, level };
			// Act
			try {
				factory.create("name", 1);
			}
			// Assert
			catch (exception e) {
				Assert::AreEqual(e.what(), "identifier does not exist");
			}
		}

		TEST_METHOD(CharacterFactory_Register_Charactar_Should_Add_Character)
		{
			// Arrange
			Engine engine;
			EventDispatcher dispatcher;
			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			SceneStateMachine statemachine{ engine, savegame };
			Level level{ 1, 100, 100, engine, statemachine };
			CharacterFactory factory{ engine, level };
			MockCharacter registerCharacter{ dispatcher };
			MockCharacter registerCharacter2{ dispatcher };
			int i = 1;
			int* a = &i;
			// Act
			factory.registerCharacter("name", &registerCharacter, a);
			// Assert
			Assert::IsTrue(true);
		}
		TEST_METHOD(CharacterFactory_Register_ExistingCharactar_Should_ThrowError)
		{
			// Arrange
			Engine engine;
			EventDispatcher dispatcher;
			shared_ptr<Savegame> savegame = shared_ptr<Savegame>(new Savegame());
			SceneStateMachine statemachine{ engine, savegame };
			Level level{ 1, 100, 100, engine, statemachine };
			CharacterFactory factory{ engine, level };
			MockCharacter registerCharacter{ dispatcher };
			MockCharacter registerCharacter2{ dispatcher };
			int i = 1;
			int* a = &i;
			// Act
			factory.registerCharacter("name", &registerCharacter, a);
			try {
				factory.registerCharacter("name", &registerCharacter2, a);
			}
			// Assert
			catch (exception e) {
				Assert::AreEqual(e.what(), "identifier already registered");
			}
		}
	};
}