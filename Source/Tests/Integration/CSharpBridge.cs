using NUnit.Framework;
using System.Runtime.InteropServices;

namespace Integration
{
    public class CSharpBridgeTests
    {
        // This assumes the C++ code is compiled into a DLL named "Framework.dll"
        [DllImport("Framework.dll")]
        private static extern int GetAnswer();

        [Test]
        public void TestGetAnswerFromCpp()
        {
            Assert.AreEqual(42, GetAnswer());
        }
    }
}
