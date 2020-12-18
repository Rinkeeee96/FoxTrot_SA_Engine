#include "pch.h"
#include "CppUnitTest.h"
#include "api.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{
	TEST_CLASS(SoundFacadeTests)
	{
	public:
		TEST_METHOD(SetFilesCreatesArray) {
			// arrange
			SoundFacade soundFacade;

			map<string, string> stringmap = {
				{"test", "test/path.test.mp3"},
				{"tes2", "test/path.test.mp3" },
			};
			// act
			soundFacade.setFiles(stringmap);

			// assert
			int mapSize = (int)stringmap.size();
			Assert::AreEqual(2, mapSize);
		}

		TEST_METHOD(LoadEffectChecksIfIdentifierExistsIsTrue) {
			SoundFacade soundFacade;
			soundFacade.addFile("test", "applause.wav");

			bool exists = soundFacade.identifierExists("test");

			Assert::IsTrue(exists);
		}

		TEST_METHOD(LoadEffectChecksIfIdentifierExistsThrowsException) {
			SoundFacade soundFacade;
			soundFacade.addFile("test", "applause.wav");
			soundFacade.addFile("boop", "applause.wav");
			try
			{
				soundFacade.identifierExists("IdontExist");
			}
			catch (exception e) {
				Assert::AreEqual(e.what(), "SoundFacade: identifier does not exist");
			}
		}

		TEST_METHOD(PlayEffectLoadsThrowsErrorWhenEffectDoesNotExist) {
			SoundFacade soundFacade;
			try
			{
				soundFacade.playEffect("IdontExist", 1);
			}
			catch (exception e) {
				Assert::AreEqual(e.what(), "SoundFacade: identifier does not exist");
			}

		}
		TEST_METHOD(IdentifierExistsThrowsExceptionWhenIdentifierNotFound) {
			SoundFacade soundFacade;
			try
			{
				soundFacade.identifierExists("IdontExist");
			}
			catch (exception e) {
				Assert::AreEqual(e.what(), "SoundFacade: identifier does not exist");
			}
		}

		TEST_METHOD(IdentifierIsLoadedReturnsTrueWhenEffectIsLoaded) {
			SoundFacade soundFacade;
			soundFacade.addFile("test", "test.mp3");

			soundFacade.loadEffect("test");
			bool exists = soundFacade.identifierIsLoaded("test");

			Assert::IsTrue(exists);
		}

		// TODO
		TEST_METHOD(FadeIn_Invalid_Fade_Time_Should_ThrowError) {
			SoundFacade soundFacade;
			try
			{
				soundFacade.fadeInMusic(-1);
			}
			catch (exception e) {
				Assert::AreEqual(e.what(), "SoundFacade: sound does not exist");
			}
		}

		TEST_METHOD(FadeOut_Invalid_Fade_Time_Should_ThrowError) {
			// Arrange
			SoundFacade soundFacade;
			// Act
			try
			{
				soundFacade.fadeOutMusic(-1);
			}
			// Assert
			catch (exception e) {
				Assert::AreEqual(e.what(), "SoundFacade: invalid fade time");
			}
		}
	};
}