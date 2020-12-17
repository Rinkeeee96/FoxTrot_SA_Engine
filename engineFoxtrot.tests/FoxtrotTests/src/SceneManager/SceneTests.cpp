#include "pch.h"
#include "CppUnitTest.h"
#include <api.h>
#include "../mocks/MockScene.h"
#include "../mocks/MockObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{
	TEST_CLASS(LayerTests)
	{
	public:
		TEST_METHOD(RemoveObject_Existing_Object_Should_Remove_Object)
		{
			// Arrange
			Layer layer;
			shared_ptr<Object> object = shared_ptr<MockObject>(new MockObject());
			// Act
			layer.addObjectInLayer(object);
			layer.removeObject(1);
			// Assert
			Assert::IsTrue(result);
		}

		TEST_METHOD(CheckIfObjectExistsTests_NonExistingObject_Should_Return_False)
		{
			// Arrange
			MockScene scene;
			// Act
			auto result = scene.checkIfObjectExists(0);
			// Assert
			Assert::IsFalse(result);
		}

		TEST_METHOD(AddNewObjectToLayer_With_RenderPhysics_Should_Have_OneLayer_WithObject)
		{
			// Arrange
			MockScene scene;
			MockObject object;
			// Act
			scene.addNewObjectToLayer(0, &object, true, false);
			auto result = scene.getAllObjectsInSceneRenderPhysics();
			// Assert
			Assert::AreEqual((int)result.size(), 1);
		}

		TEST_METHOD(AddNewObjectToLayer_With_AllWaysDraw_Should_Have_OneLayer_WithObject)
		{
			// Arrange
			MockScene scene;
			MockObject object;
			// Act
			scene.addNewObjectToLayer(0, &object, false, true);
			auto result = scene.getAllObjectsInScene();
			// Assert
			Assert::AreEqual((int)result.size(), 1);
		}

		TEST_METHOD(GetAllDrawablesInScene_OneDrawables_Should_Return_Vector)
		{
			// Arrange
			MockScene scene;
			MockDrawable object;
			// Act
			scene.addNewObjectToLayer(0, &object, false, true);
			auto result = scene.getAllDrawablesInScene();
			// Assert
			Assert::AreEqual((int)result.size(), 1);
		}

		//vector <Object*> API getAllObjectsInScene();
		TEST_METHOD(GetAllDrawablesInScene_NoDrawables_Should_Return_Empty_Vector)
		{
			// Arrange
			MockScene scene;
			MockObject object;
			// Act
			scene.addNewObjectToLayer(0, &object, false, true);
			auto result = scene.getAllDrawablesInScene();
			// Assert
			Assert::AreEqual((int)result.size(), 0);
		}
		TEST_METHOD(GetAllDrawablesInScene_OneDrawables_OneObject_Should_Return_Vector)
		{
			// Arrange
			MockScene scene;
			MockObject object;
			MockDrawable drawable;
			// Act
			scene.addNewObjectToLayer(0, &object, false, true);
			scene.addNewObjectToLayer(0, &drawable, false, true);
			auto result = scene.getAllDrawablesInScene();
			// Assert
			Assert::AreEqual((int)result.size(), 1);
		}

		TEST_METHOD(GetObject_ExistingObject_Should_Return_Object)
		{
			// Arrange
			MockScene scene;
			MockObject object;
			// Act
			scene.addNewObjectToLayer(0, &object, false, true);
			auto result = scene.getObject(1);
			// Assert
			Assert::IsTrue(true);
		}

		TEST_METHOD(RemoveObject_NonExisting_Object_Should_ThrowError)
		{
			// Arrange
			MockScene scene;
			MockObject object;
			Layer layer;
			shared_ptr<Object> object = shared_ptr<MockObject>(new MockObject());
			// Act
			layer.addObjectInLayer(object);
			try {
				auto result = scene.getObject(1);
			}
			// Assert
			catch (exception e) {
				Assert::AreEqual(e.what(), "object does not exist");
			}
		}

		TEST_METHOD(ClearObjects_Should_Remove_All_Objects)
		{
			// Arrange
			Layer layer;
			shared_ptr<Object> object = shared_ptr<MockObject>(new MockObject());
			// Act
			layer.addObjectInLayer(object);
			layer.clearObjects();
			// Assert
			Assert::IsTrue(object.getIsRemoved());
		}

		TEST_METHOD(GetObject_NonExistingObject_Should_Not_Remove_Object)
		{
			// Arrange
			MockScene scene;
			MockObject object;
			MockObject object2;
			// Act
			scene.addNewObjectToLayer(0, &object, false, true);
			scene.removeObjectFromScene(&object2);
			// Assert
			Assert::IsFalse(object.getIsRemoved());
		}

		TEST_METHOD(getLayers_TwoExistingLayers_Should_Return_Map_With_Layers)
		{
			// Arrange
			MockScene scene;
			MockObject object;
			// Act
			scene.addNewObjectToLayer(0, &object, false, true);
			scene.createLayer(25, 0, 0);
			// Assert
			Assert::AreEqual((int)scene.getLayers().count(0), 1);
			Assert::AreEqual((int)scene.getLayers().count(25), 1);
		}

		TEST_METHOD(createLayer_Should_Create_Empty_Layer)
		{
			// Arrange
			MockScene scene;
			// Act
			scene.createLayer(25, 0, 0);
			// Assert
			Assert::AreEqual((int)scene.getLayers().count(25), 1);
		}

		TEST_METHOD(GetHighestLayerIndex_MutipleLayers_Should_Return_Highest_Zindex)
		{
			// Arrange
			MockScene scene;
			MockObject object;
			// Act
			scene.addNewObjectToLayer(0, &object, false, true);
			scene.createLayer(25, 0, 0);
			// Assert
			Assert::AreEqual((int)scene.getHighestLayerIndex(), 25);
		}

		TEST_METHOD(GetHighestLayerIndex_ZeroLayers_Should_Return_0)
		{
			// Arrange
			MockScene scene;
			// Act
			auto result = scene.getHighestLayerIndex();
			// Assert
			Assert::AreEqual((int)result, 0);
		}

		TEST_METHOD(ObjectExists_Existing_Object_Should_Return_True)
		{
			// Arrange
			MockScene scene;
			Layer layer;
			shared_ptr<Object> object = shared_ptr<MockObject>(new MockObject());
			// Act
			layer.addObjectInLayer(object);
			// Assert
			Assert::AreEqual((int)scene.getLayers().count(1), 1);
		}

		TEST_METHOD(ObjectExists_NonExisting_Object_Should_Return_False)
		{
			// Arrange
			MockScene scene;
			Layer layer;
			shared_ptr<Object> object = shared_ptr<MockObject>(new MockObject());
			// Act
			layer.addObjectInLayer(object);
			// Assert
			Assert::AreEqual((int)scene.getLayers().count(1), 1);
		}

		TEST_METHOD(GetSpecificObjectInLayer_NonExisting_Object_ThrowError)
		{
			// Arrange
			MockScene scene;
			Layer layer;
			shared_ptr<Object> object = shared_ptr<MockObject>(new MockObject());
			// Act
			layer.addObjectInLayer(object);
			try {
				layer.getObjectsInLayer();
			}
			// Assert
			Assert::AreEqual((int)scene.getLayers().count(1), 0);
		}

		TEST_METHOD(AddObjectInLayer_Should_Have_Single_Object)
		{
			// Arrange
			MockScene scene;
			Layer layer;
			shared_ptr<Object> object = shared_ptr<MockObject>(new MockObject());
			// Act
			layer.addObjectInLayer(object);
			// Assert
			Assert::AreEqual((int)scene.getLayers().count(1), 1);
		}
	};
}