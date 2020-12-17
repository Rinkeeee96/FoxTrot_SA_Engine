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
			auto result = layer.objectExists(1);
			Assert::IsFalse(result);
		}

		TEST_METHOD(RemoveObject_NonExisting_Object_Should_ThrowError)
		{
			// Arrange
			Layer layer;
			shared_ptr<Object> object = shared_ptr<MockObject>(new MockObject());
			// Act
			layer.addObjectInLayer(object);
			try {
				layer.removeObject(0);
			}
			// Assert
			catch (exception e) {
				Assert::AreEqual(e.what(), "Layer: object does not exist");
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
			auto result = layer.objectExists(1);
			Assert::IsFalse(result);
		}

		TEST_METHOD(ObjectExists_Existing_Object_Should_Return_True)
		{
			// Arrange
			Layer layer;
			shared_ptr<Object> object = shared_ptr<MockObject>(new MockObject());
			// Act
			layer.addObjectInLayer(object);
			// Assert
			auto result = layer.objectExists(1);
			Assert::IsTrue(result);
		}

		TEST_METHOD(ObjectExists_NonExisting_Object_Should_Return_False)
		{
			// Arrange
			Layer layer;
			shared_ptr<Object> object = shared_ptr<MockObject>(new MockObject());
			// Act
			layer.addObjectInLayer(object);
			// Assert
			auto result = layer.objectExists(0);
			Assert::IsFalse(result);
		}

		TEST_METHOD(GetSpecificObjectInLayer_NonExisting_Object_ThrowError)
		{
			// Arrange
			Layer layer;
			shared_ptr<Object> object = shared_ptr<MockObject>(new MockObject());
			// Act
			layer.addObjectInLayer(object);
			try {
				layer.getObjectsInLayer();
			}
			// Assert
			catch (exception e) {
				Assert::AreEqual(e.what(), "object does not exist");
			}
		}

		TEST_METHOD(AddObjectInLayer_Should_Have_Single_Object)
		{
			// Arrange
			Layer layer;
			shared_ptr<Object> object = shared_ptr<MockObject>(new MockObject());
			// Act
			layer.addObjectInLayer(object);
			// Assert
			auto result = layer.getObjectsInLayer();
			auto x = result[1];
			Assert::AreEqual(x->getObjectId(), 1);
		}
	};
}