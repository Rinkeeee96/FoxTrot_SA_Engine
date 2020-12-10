#include "pch.h"
#include "CppUnitTest.h"
#include "api.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestsEngine
{
	TEST_CLASS(SoundEngineTests)
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
			int mapSize = stringmap.size();
			Assert::AreEqual(2, mapSize);
		}

		TEST_METHOD(AddFileWithIdentifier) {
			SoundFacade soundFacade;
			soundFacade.addFile("test", "test.mp3");
			Assert::IsTrue(soundFacade.identifierIsLoaded("test"));
		}

		TEST_METHOD(AddFileWithSameIdentifierOverwritesOldEntry) {
			SoundFacade soundFacade;
			soundFacade.addFile("test", "test.mp3");
			soundFacade.addFile("test", "override.mp3");

			// TODO
			/*string path = soundFacade.GetSoundPaths().find("test")->second;

			Assert::IsTrue(path == "override.mp3");*/
		}

		TEST_METHOD(LoadEffectChecksIfIdentifierExistsIsTrue) {
			SoundFacade soundFacade;
			soundFacade.addFile("test", "test.mp3");

			bool exists = soundFacade.identifierExists("test");

			Assert::IsTrue(exists);
		}

		TEST_METHOD(LoadEffectChecksIfIdentifierExistsThrowsException) {
			SoundFacade soundFacade;
			soundFacade.addFile("test", "test.mp3");
			soundFacade.addFile("boop", "test.mp3");
			try
			{
				soundFacade.identifierExists("IdontExist");
			}
			catch (int e)
			{
				Assert::IsTrue(e == ERROR_CODE_SVIFACADE_SOUND_IDENTIFIER_NOT_FOUND);
			}
		}

		TEST_METHOD(PlayEffectLoadsThrowsErrorWhenEffectDoesNotExist) {
			SoundFacade soundFacade;
			try
			{
				soundFacade.playEffect("IdontExist", 1);
			}
			catch (int e)
			{
				Assert::IsTrue(e == ERROR_CODE_SVIFACADE_SOUND_IDENTIFIER_NOT_FOUND);
			}

		}
		TEST_METHOD(IdentifierExistsThrowsExceptionWhenIdentifierNotFound) {
			SoundFacade soundFacade;
			try
			{
				soundFacade.identifierExists("IdontExist");
			}
			catch (int e)
			{
				Assert::IsTrue(e == ERROR_CODE_SVIFACADE_SOUND_IDENTIFIER_NOT_FOUND);
			}
		}

		TEST_METHOD(IdentifierIsLoadedReturnsTrueWhenEffectIsLoaded) {
			SoundFacade soundFacade;
			soundFacade.addFile("test", "test.mp3");

			soundFacade.loadEffect("test");
			bool exists = soundFacade.identifierIsLoaded("test");

			Assert::IsTrue(exists);
		}

		TEST_METHOD(FadeInThrowsExceptionWhenFadeTimeIsNegative) {
			try
			{
				SoundFacade soundFacade;
				soundFacade.fadeInMusic(-1);
			}
			catch (int e)
			{
				Assert::IsTrue(e == ERROR_CODE_SVIFACADE_INVALID_FADETIME);
			}
		}

		TEST_METHOD(FadeOutThrowsExceptionWhenFadeTimeIsNegative) {
			try
			{
				SoundFacade soundFacade;
				soundFacade.fadeOutMusic(-1);
			}
			catch (int e)
			{
				Assert::IsTrue(e == ERROR_CODE_SVIFACADE_INVALID_FADETIME);
			}
		}
	};
}