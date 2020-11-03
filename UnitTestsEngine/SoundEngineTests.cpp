#include "pch.h"
//#include "CppUnitTest.h"
//#include "../api.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace UnitTestsEngine
//{
//	TEST_CLASS(SoundEngineTests)
//	{
//	public:
//		TEST_METHOD(SetFilesCreatesArray) {
//			// arrange
//			SoundFacade soundFacade;
//
//			unordered_map<string, string> stringmap = {
//				{"test", "test/path.test.mp3"},
//				{"tes2", "test/path.test.mp3" },
//			};
//			// act
//			soundFacade.SetFiles(stringmap);
//
//			// assert
//			int pathSize = soundFacade.GetSoundPaths().size();
//			int mapSize = stringmap.size();
//			Assert::AreEqual(pathSize, mapSize);
//		}
//
//		TEST_METHOD(AddFileWithIdentifier) {
//			SoundFacade soundFacade;
//			soundFacade.AddFile("test", "test.mp3");
//			Assert::IsTrue(soundFacade.GetSoundPaths().find("test")->second == "test.mp3");
//		}
//
//		TEST_METHOD(AddFileWithSameIdentifierOverwritesOldEntry) {
//			SoundFacade soundFacade;
//			soundFacade.AddFile("test", "test.mp3");
//			soundFacade.AddFile("test", "override.mp3");
//
//			string path = soundFacade.GetSoundPaths().find("test")->second;
//
//			Assert::IsTrue(path == "override.mp3");
//		}
//
//		TEST_METHOD(LoadEffectChecksIfIdentifierExistsIsTrue) {
//			SoundFacade soundFacade;
//			soundFacade.AddFile("test", "test.mp3");
//
//			bool exists = soundFacade.IdentifierExists("test");
//
//			Assert::IsTrue(exists);
//		}
//
//		TEST_METHOD(LoadEffectChecksIfIdentifierExistsThrowsException) {
//			SoundFacade soundFacade;
//			soundFacade.AddFile("test", "test.mp3");
//			soundFacade.AddFile("boop", "test.mp3");
//			try
//			{
//				soundFacade.IdentifierExists("IdontExist");
//			}
//			catch (int e)
//			{
//				Assert::IsTrue(e == ERROR_CODE_SVIFACADE_SOUND_IDENTIFIER_NOT_FOUND);
//			}
//		}
//
//		TEST_METHOD(PlayEffectLoadsThrowsErrorWhenEffectDoesNotExist) {
//			SoundFacade soundFacade;
//			try
//			{
//				soundFacade.PlayEffect("IdontExist", 1);
//			}
//			catch (int e)
//			{
//				Assert::IsTrue(e == ERROR_CODE_SVIFACADE_SOUND_IDENTIFIER_NOT_FOUND);
//			}
//
//		}
//		TEST_METHOD(IdentifierExistsThrowsExceptionWhenIdentifierNotFound) {
//			SoundFacade soundFacade;
//			try
//			{
//				soundFacade.IdentifierExists("IdontExist");
//			}
//			catch (int e)
//			{
//				Assert::IsTrue(e == ERROR_CODE_SVIFACADE_SOUND_IDENTIFIER_NOT_FOUND);
//			}
//		}
//
//		TEST_METHOD(IdentifierIsLoadedReturnsTrueWhenEffectIsLoaded) {
//			SoundFacade soundFacade;
//			soundFacade.AddFile("test", "test.mp3");
//
//			soundFacade.LoadEffect("test");
//			bool exists = soundFacade.IdentifierIsLoaded("test");
//
//			Assert::IsTrue(exists);
//		}
//
//		TEST_METHOD(FadeInThrowsExceptionWhenFadeTimeIsNegative) {
//			try
//			{
//				SoundFacade soundFacade;
//				soundFacade.FadeInMusic(-1);
//			}
//			catch (int e)
//			{
//				Assert::IsTrue(e == ERROR_CODE_SVIFACADE_INVALID_FADETIME);
//			}
//		}
//
//		TEST_METHOD(FadeOutThrowsExceptionWhenFadeTimeIsNegative) {
//			try
//			{
//				SoundFacade soundFacade;
//				soundFacade.FadeOutMusic(-1);
//			}
//			catch (int e)
//			{
//				Assert::IsTrue(e == ERROR_CODE_SVIFACADE_INVALID_FADETIME);
//			}
//		}
//	};
//}