#include "pch.h"
#include "CppUnitTest.h"
#include <api.h>
#include "../mocks/MockScene.h"
#include "../mocks/MockObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{
	TEST_CLASS(SceneTests)
	{
	public:
		TEST_METHOD(CheckIfObjectExistsTests_ExistingObject_Should_Return_True)
		{
			// Arrange
			Scene* scene = new MockScene();
			Object* object = new MockObject();
			// Act
			scene->addNewObjectToLayer(0, object, false, false);
			auto result = scene->checkIfObjectExists(1);
			// Assert
			Assert::IsTrue(result);

			delete scene;
			delete object;
		}

		TEST_METHOD(CheckIfObjectExistsTests_NonExistingObject_Should_Return_False)
		{
			// Arrange
			Scene* scene = new MockScene();
			// Act
			auto result = scene->checkIfObjectExists(0);
			// Assert
			Assert::IsFalse(result);

			delete scene;
		}

		TEST_METHOD(AddNewObjectToLayer_With_RenderPhysics_Should_Have_OneLayer_WithObject)
		{
			// Arrange
			Scene* scene = new MockScene();
			Object* object = new MockObject();
			// Act
			scene->addNewObjectToLayer(0, object, true, false);
			auto result = scene->getAllObjectsInSceneRenderPhysics();
			// Assert
			Assert::AreEqual((int)result.size(), 1);

			delete scene;
			delete object;
		}

		TEST_METHOD(AddNewObjectToLayer_With_AllWaysDraw_Should_Have_OneLayer_WithObject)
		{
			// Arrange
			Scene* scene = new MockScene();
			Object* object = new MockObject();
			// Act
			scene->addNewObjectToLayer(0, object, false, true);
			auto result = scene->getAllObjectsInScene();
			// Assert
			Assert::AreEqual((int)result.size(), 1);

			delete scene;
			delete object;
		}

		TEST_METHOD(GetAllDrawablesInScene_OneDrawables_Should_Return_Vector)
		{
			// Arrange
			Scene* scene = new MockScene();
			Object* object = new MockDrawable();
			// Act
			scene->addNewObjectToLayer(0, object, false, true);
			auto result = scene->getAllDrawablesInScene();
			// Assert
			Assert::AreEqual((int)result.size(), 1);

			delete scene;
			delete object;
		}

		//vector <Object*> API getAllObjectsInScene();
		TEST_METHOD(GetAllDrawablesInScene_NoDrawables_Should_Return_Empty_Vector)
		{
			// Arrange
			Scene* scene = new MockScene();
			Object* object = new MockObject();
			// Act
			scene->addNewObjectToLayer(0, object, false, true);
			auto result = scene->getAllDrawablesInScene();
			// Assert
			Assert::AreEqual((int)result.size(), 0);

			delete scene;
			delete object;
		}
		TEST_METHOD(GetAllDrawablesInScene_OneDrawables_OneObject_Should_Return_Vector)
		{
			// Arrange
			Scene* scene = new MockScene();
			Object* object = new MockObject();
			Object* drawable = new MockDrawable();
			// Act
			scene->addNewObjectToLayer(0, object, false, true);
			scene->addNewObjectToLayer(0, drawable, false, true);
			auto result = scene->getAllDrawablesInScene();
			// Assert
			Assert::AreEqual((int)result.size(), 1);

			delete scene;
			delete drawable;
			delete object;
		}

		TEST_METHOD(GetObject_ExistingObject_Should_Return_Object)
		{
			// Arrange
			Scene* scene = new MockScene();
			Object* object = new MockObject();
			// Act
			scene->addNewObjectToLayer(0, object, false, true);
			auto result = scene->getObject(1);
			// Assert
			Assert::IsTrue(true);

			delete scene;
			delete object;
		}

		TEST_METHOD(GetObject_NonExistingObject_Should_ThrowError)
		{
			// Arrange
			Scene* scene = new MockScene();
			// Act
			try {
				auto result = scene->getObject(1);
			}
			// Assert
			catch (exception e) {
				Assert::AreEqual(e.what(), "object does not exist");
			}

			delete scene;
		}

		TEST_METHOD(RemoveExistingObject_Should_Remove_Objects)
		{
			// Arrange
			Scene* scene = new MockScene();
			Object* object = new MockObject();
			// Act
			scene->addNewObjectToLayer(0, object, false, true);
			scene->removeObjectFromScene(object);
			// Assert
			Assert::IsTrue(object->getIsRemoved());

			delete scene;
			delete object;
		}

		TEST_METHOD(GetObject_NonExistingObject_Should_Not_Remove_Object)
		{
			// Arrange
			Scene* scene = new MockScene();
			Object* object = new MockObject();
			Object* object2 = new MockObject();
			// Act
			scene->addNewObjectToLayer(0, object, false, true);
			scene->removeObjectFromScene(object2);
			// Assert
			Assert::IsFalse(object->getIsRemoved());

			delete scene;
			delete object;
			delete object2;
		}

		TEST_METHOD(getLayers_TwoExistingLayers_Should_Return_Map_With_Layers)
		{
			// Arrange
			Scene* scene = new MockScene();
			Object* object = new MockObject();
			// Act
			scene->addNewObjectToLayer(0, object, false, true);
			scene->createLayer(25, 0, 0);
			// Assert
			Assert::AreEqual((int)scene->getLayers().count(0), 1);
			Assert::AreEqual((int)scene->getLayers().count(25), 1);

			delete scene;
			delete object;
		}

		TEST_METHOD(createLayer_Should_Create_Empty_Layer)
		{
			// Arrange
			Scene* scene = new MockScene();
			// Act
			scene->createLayer(25, 0, 0);
			// Assert
			Assert::AreEqual((int)scene->getLayers().count(25), 1);

			delete scene;
		}

		TEST_METHOD(GetHighestLayerIndex_MutipleLayers_Should_Return_Highest_Zindex)
		{
			// Arrange
			Scene* scene = new MockScene();
			Object* object = new MockObject();
			// Act
			scene->addNewObjectToLayer(0, object, false, true);
			scene->createLayer(25, 0, 0);
			// Assert
			Assert::AreEqual((int)scene->getHighestLayerIndex(), 25);

			delete scene;
			delete object;
		}

		TEST_METHOD(GetHighestLayerIndex_ZeroLayers_Should_Return_0)
		{
			// Arrange
			Scene* scene = new MockScene();
			// Act
			auto result = scene->getHighestLayerIndex();
			// Assert
			Assert::AreEqual((int)result, 0);

			delete scene;
		}

		//API void addLayerOnZIndex(const int zIndex, Layer* _layer);
		TEST_METHOD(AddLayerOnZIndex_NoLayer_On_ZIndex_Should_Add_Layer)
		{
			// Arrange
			Scene* scene = new MockScene();
			Layer* layer = new Layer();
			// Act
			scene->addLayerOnZIndex(1, layer);
			// Assert
			Assert::AreEqual((int)scene->getLayers().count(1), 1);

			delete scene;
			delete layer;
		}

		TEST_METHOD(AddLayerOnZIndex_ExistingLayer_On_ZIndex_Should_Add_Layer_And_Remove_Old_Layer)
		{
			// Arrange
			Scene* scene = new MockScene();
			Layer* layer = new Layer();
			Layer* layer2 = new Layer();
			// Act
			scene->addLayerOnZIndex(1, layer);
			scene->addLayerOnZIndex(1, layer2);
			// Assert
			Assert::AreEqual((int)scene->getLayers().count(1), 1);

			delete scene;
			delete layer;
			delete layer2;
		}

		//API void removeLayer(const int zIndex);
		TEST_METHOD(Remove_ExistingLayer_Should_Remove_Layer)
		{
			// Arrange
			Scene* scene = new MockScene();
			Layer* layer = new Layer();
			// Act
			scene->addLayerOnZIndex(1, layer);
			scene->removeLayer(1);
			// Assert
			Assert::AreEqual((int)scene->getLayers().count(1), 0);

			delete scene;
			delete layer;
		}

		TEST_METHOD(Remove_ExistingLayer_Should_Do_Nothing)
		{
			// Arrange
			Scene* scene = new MockScene();
			Layer* layer = new Layer();
			// Act
			scene->addLayerOnZIndex(1, layer);
			scene->removeLayer(2);
			// Assert
			Assert::AreEqual((int)scene->getLayers().count(1), 1);

			delete scene;
			delete layer;
		}
	};
}