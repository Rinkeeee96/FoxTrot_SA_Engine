#include "pch.h"
#include "CppUnitTest.h"
#include <api.h>
#include "../mocks/MockScene.h"
#include "../mocks/MockObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{

	TEST_CLASS(VideoEngineTests)
	{
	public:
		TEST_METHOD(LoadImage_Valid_Path_Should_Load_Image_Correctly)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher;
			VideoEngine videoEngine { frameData };
			videoEngine.start(dispatcher);
			shared_ptr<Drawable> drawable = shared_ptr<Drawable>(new Drawable());
			shared_ptr<SpriteObject> spriteObject= shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, "TestAssets/testPNG.png" });
			drawable->registerSprite(1, spriteObject);
			// Act
			videoEngine.loadImage(spriteObject);
			// Assert
			Assert::IsTrue(true);
		}

		TEST_METHOD(LoadImage_InValid_Should_ThrowError)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher;
			VideoEngine videoEngine{ frameData };
			videoEngine.start(dispatcher);
			shared_ptr<Drawable> drawable = shared_ptr<Drawable>(new Drawable());
			shared_ptr<SpriteObject> spriteObject = shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, NULL });
			drawable->registerSprite(1, spriteObject);
			// Act
			try {
				videoEngine.loadImage(spriteObject);
			}
			// Assert
			catch(exception e) {
				Assert::AreEqual(e.what(), "Invalid file name");
			}
		}

		TEST_METHOD(RenderCopy_Valid_File_Should_Render_Copy)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher;
			VideoEngine videoEngine{ frameData };
			videoEngine.start(dispatcher);
			shared_ptr<Drawable> drawable = shared_ptr<Drawable>(new Drawable());
			shared_ptr<SpriteObject> spriteObject = shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, "TestAssets/testPNG.png" });
			drawable->registerSprite(1, spriteObject);
			drawable->changeToState(1);
			// Act
			videoEngine.renderCopy(drawable);
			// Assert
			Assert::IsTrue(true);
		}

		TEST_METHOD(RenderCopy_InValid_File_Should_ThrowError)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher;
			VideoEngine videoEngine{ frameData };
			videoEngine.start(dispatcher);
			shared_ptr<Drawable> drawable = shared_ptr<Drawable>(new Drawable());
			shared_ptr<SpriteObject> spriteObject = shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, NULL });
			drawable->registerSprite(1, spriteObject);
			drawable->changeToState(1);
			// Act
			try {
				videoEngine.renderCopy(drawable);
			}
			// Assert
			catch (exception e) {
				Assert::AreEqual(e.what(), "Invalid file name");
			}
		}

		TEST_METHOD(CalculateOffsetWithObjectToFollow_Should_Have_No_Offset)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher;
			VideoEngine videoEngine{ frameData };
			videoEngine.start(dispatcher);
			shared_ptr<Drawable> drawable = shared_ptr<Drawable>(new Drawable());
			shared_ptr<SpriteObject> spriteObject = shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, NULL });
			drawable->registerSprite(1, spriteObject);
			drawable->changeToState(1);
			// Act
			videoEngine.calculateOffset(drawable, 1024, 1024);
			// Assert
			Assert::AreEqual(0, videoEngine.getVideoFacade().getXCameraOffset());
			Assert::AreEqual(0, videoEngine.getVideoFacade().getYCameraOffset());
		}

		TEST_METHOD(CalculateOffsetWithObjectToFollow_Should_X_Have_No_Offset)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher;
			VideoEngine videoEngine{ frameData };
			videoEngine.start(dispatcher);
			shared_ptr<Drawable> drawable = shared_ptr<Drawable>(new Drawable());
			drawable->setPositionX(3024 - 100);
			shared_ptr<SpriteObject> spriteObject = shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, NULL });;
			drawable->registerSprite(1, spriteObject);
			drawable->changeToState(1);
			// Act
			videoEngine.calculateOffset(drawable, 3024, 1024);
			// Assert
			Assert::AreNotEqual(0, videoEngine.getVideoFacade().getXCameraOffset());
			Assert::AreEqual(0, videoEngine.getVideoFacade().getYCameraOffset());
		}

		TEST_METHOD(CalculateOffsetWithObjectToFollow_Should_Y_Have_No_Offset)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher;
			VideoEngine videoEngine{ frameData };
			videoEngine.start(dispatcher);
			shared_ptr<Drawable> drawable = shared_ptr<Drawable>(new Drawable());
			drawable->setPositionX(0);
			drawable->setPositionY(3024 - 3024/2);
			shared_ptr<SpriteObject> spriteObject = shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, NULL });
			drawable->registerSprite(1, spriteObject);
			drawable->changeToState(1);
			// Act
			videoEngine.calculateOffset(drawable, 3024, 1024);
			// Assert
			Assert::AreEqual(0, videoEngine.getVideoFacade().getXCameraOffset());
			Assert::AreNotEqual(0, videoEngine.getVideoFacade().getYCameraOffset());
		}

		TEST_METHOD(CheckObjectInScreen_Outside_North_Side_Should_Return_False)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher;
			VideoEngine videoEngine{ frameData };
			videoEngine.start(dispatcher);
			shared_ptr<Drawable> drawable = shared_ptr<Drawable>(new Drawable());
			drawable->setPositionX(100);
			drawable->setPositionY(-1);
			drawable->setWidth(10);
			drawable->setHeight(10);
			shared_ptr<SpriteObject> spriteObject = shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, NULL });
			drawable->registerSprite(1, spriteObject);
			drawable->changeToState(1);
			// Act
			auto result = videoEngine.checkObjectInScreen(drawable);
			// Assert
			Assert::IsFalse(result);
		}

		TEST_METHOD(CheckObjectInScreen_Inside_North_Side_Should_Return_True)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher;
			VideoEngine videoEngine{ frameData };
			videoEngine.start(dispatcher);
			shared_ptr<Drawable> drawable = shared_ptr<Drawable>(new Drawable());
			drawable->setPositionX(100);
			drawable->setPositionY(1);
			drawable->setWidth(10);
			drawable->setHeight(10);
			shared_ptr<SpriteObject> spriteObject = shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, NULL });
			drawable->registerSprite(1, spriteObject);
			drawable->changeToState(1);
			// Act
			auto result = videoEngine.checkObjectInScreen(drawable);
			// Assert
			Assert::IsTrue(result);
		}

		TEST_METHOD(CheckObjectInScreen_Outside_West_Side_Should_Return_False)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher;
			VideoEngine videoEngine{ frameData };
			videoEngine.start(dispatcher);
			shared_ptr<Drawable> drawable = shared_ptr<Drawable>(new Drawable());
			drawable->setPositionX(-11);
			drawable->setPositionY(100);
			drawable->setWidth(10);
			drawable->setHeight(10);
			shared_ptr<SpriteObject> spriteObject = shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, NULL });
			drawable->registerSprite(1, spriteObject);
			drawable->changeToState(1);
			// Act
			auto result = videoEngine.checkObjectInScreen(drawable);
			// Assert
			Assert::IsFalse(result);
		}

		TEST_METHOD(CheckObjectInScreen_Inside_West_Side_Should_Return_True)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher;
			VideoEngine videoEngine{ frameData };
			videoEngine.start(dispatcher);
			shared_ptr<Drawable> drawable = shared_ptr<Drawable>(new Drawable());
			drawable->setPositionX(-9);
			drawable->setPositionY(100);
			drawable->setWidth(10);
			drawable->setHeight(10);
			shared_ptr<SpriteObject> spriteObject = shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, NULL });
			drawable->registerSprite(1, spriteObject);
			drawable->changeToState(1);
			// Act
			auto result = videoEngine.checkObjectInScreen(drawable);
			// Assert
			Assert::IsTrue(result);
		}

		TEST_METHOD(CheckObjectInScreen_Outside_South_Side_Should_Return_False)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher;
			VideoEngine videoEngine{ frameData };
			videoEngine.start(dispatcher);
			shared_ptr<Drawable> drawable = shared_ptr<Drawable>(new Drawable());
			drawable->setPositionX(100);
			drawable->setPositionY(WINDOW_HEIGHT + 11);
			drawable->setWidth(10);
			drawable->setHeight(10);
			shared_ptr<SpriteObject> spriteObject = shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, NULL });
			drawable->registerSprite(1, spriteObject);
			drawable->changeToState(1);
			// Act
			auto result = videoEngine.checkObjectInScreen(drawable);
			// Assert
			Assert::IsFalse(result);
		}

		TEST_METHOD(CheckObjectInScreen_Inside_South_Side_Should_Return_True)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher;
			VideoEngine videoEngine{ frameData };
			videoEngine.start(dispatcher);
			shared_ptr<Drawable> drawable = shared_ptr<Drawable>(new Drawable());
			drawable->setPositionX(100);
			drawable->setPositionY(WINDOW_HEIGHT + 9);
			drawable->setWidth(10);
			drawable->setHeight(10);
			shared_ptr<SpriteObject> spriteObject = shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, NULL });
			drawable->registerSprite(1, spriteObject);
			drawable->changeToState(1);
			// Act
			auto result = videoEngine.checkObjectInScreen(drawable);
			// Assert
			Assert::IsTrue(result);
		}

		TEST_METHOD(CheckObjectInScreen_Outside_East_Side_Should_Return_False)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher;
			VideoEngine videoEngine{ frameData };
			videoEngine.start(dispatcher);
			shared_ptr<Drawable> drawable = shared_ptr<Drawable>(new Drawable());
			drawable->setPositionX(WINDOW_WIDTH + 1);
			drawable->setPositionY(100);
			drawable->setWidth(10);
			drawable->setHeight(10);
			shared_ptr<SpriteObject> spriteObject = shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, NULL });
			drawable->registerSprite(1, spriteObject);
			drawable->changeToState(1);
			// Act
			auto result = videoEngine.checkObjectInScreen(drawable);
			// Assert
			Assert::IsFalse(result);
		}

		TEST_METHOD(CheckObjectInScreen_Inside_East_Side_Should_Return_True)
		{
			// Arrange
			unique_ptr<FrameData> frameData = make_unique<FrameData>();
			EventDispatcher dispatcher;
			VideoEngine videoEngine{ frameData };
			videoEngine.start(dispatcher);
			shared_ptr<Drawable> drawable = shared_ptr<Drawable>(new Drawable());
			drawable->setPositionX(WINDOW_WIDTH - 1);
			drawable->setPositionY(100);
			drawable->setWidth(10);
			drawable->setHeight(10);
			shared_ptr<SpriteObject> spriteObject = shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, NULL });
			drawable->registerSprite(1, spriteObject);
			drawable->changeToState(1);
			// Act
			auto result = videoEngine.checkObjectInScreen(drawable);
			// Assert
			Assert::IsTrue(result);
		}
	};
}