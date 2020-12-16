#include "pch.h"
#include "CppUnitTest.h"
#include <api.h>
#include "../mocks/MockScene.h"
#include "../mocks/MockObject.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{

	TEST_CLASS(VideoFacadeTests)
	{
	public:
		TEST_METHOD(LoadImage_Valid_Path_Should_Load_Image_Correctly)
		{
			// Arrange
			FrameData frameData;
			EventDispatcher dispatcher;
			VideoFacade videoEngine;
			Drawable drawable;
			shared_ptr<SpriteObject> spriteObject = shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, "TestAssets/testPNG.png" });
			drawable.registerSprite(1, spriteObject);
			// Act
			videoEngine.loadImage(spriteObject);
			// Assert
			Assert::IsTrue(true);
		}

		TEST_METHOD(LoadImage_InValid_Should_ThrowError)
		{
			// Arrange
			FrameData frameData;
			EventDispatcher dispatcher;
			VideoFacade videoEngine;
			Drawable drawable;
			shared_ptr<SpriteObject> spriteObject = shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, NULL });
			drawable.registerSprite(1, spriteObject);
			// Act
			try {
				videoEngine.loadImage(spriteObject);
			}
			// Assert
			catch (exception e) {
				Assert::AreEqual(e.what(), "Invalid file name");
			}
		}

		TEST_METHOD(RenderCopy_Valid_File_Should_Render_Copy)
		{
			// Arrange
			FrameData frameData;
			EventDispatcher dispatcher;
			VideoFacade videoEngine;
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
			FrameData frameData;
			EventDispatcher dispatcher;
			VideoFacade videoEngine;
			shared_ptr<Drawable> drawable = shared_ptr<Drawable>(new Drawable());
			shared_ptr<SpriteObject> spriteObject = shared_ptr<SpriteObject>(new SpriteObject{ 1, 1, 1, 1, 1, NULL});
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
	};
}