using NUnit.Framework;
using System.Runtime.InteropServices;

namespace Integration
{
    public class CSharpBridgeTests
    {
        // This assumes the C++ code is compiled into a DLL named "Framework.dll"
        [DllImport("Framework.dll")]
        private static extern int GetAnswer();

        [DllImport("Framework.dll")]
        private static extern bool TriggerGauntletTest(string testName);

        [Test]
        public void TestGetAnswerFromCpp()
        {
            Assert.AreEqual(42, GetAnswer());
        }

        [Test]
        public void TestTriggerGauntletTest()
        {
            bool success = TriggerGauntletTest("MyFirstGauntletTest");
            Assert.IsTrue(success, "Gauntlet test should be triggered successfully.");
        }
    }
}
