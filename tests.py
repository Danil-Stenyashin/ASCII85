import unittest
import subprocess
import base64

class TestASCII85Encoder(unittest.TestCase):
    test_cases_encoder = [
        (b"test", b"BOu!r"),
        (b"data", b"DG_c+"),
        (b"abcd", b"@:E_W"),
        (b"9876", b"7GZ+j"),
        (b"\x00\x00\x00\x01", b"!!!!\""), 
    ]

    def test_encoder_valid(self):
        for input_data, expected in self.test_cases_encoder:
            with self.subTest(input_data=input_data):
                result = subprocess.run(
                    ["./ascii85", "-e"],
                    input=input_data,
                    capture_output=True,
                    check=True
                )
                self.assertEqual(result.stdout.strip(), base64.a85encode(input_data, adobe=False).strip())
                self.assertEqual(result.returncode, 0)


class TestASCII85Decoder(unittest.TestCase):
    test_cases_decoder = [
        (b"BOu!r", b"test"),
        (b"DG_c+", b"data"),
        (b"@:E_W", b"abcd"),
        (b"7GZ+j", b"9876"),
        (b"!!!!\"", b"\x00\x00\x00\x01"), 
    ]

    def test_decoder_valid(self):
        for encoded_data, expected in self.test_cases_decoder:
            with self.subTest(encoded_data=encoded_data):
                result = subprocess.run(
                    ["./ascii85", "-d"],
                    input=encoded_data,
                    capture_output=True,
                    check=True
                )
                self.assertEqual(result.stdout.strip(), base64.a85decode(encoded_data, adobe=False).strip())
                self.assertEqual(result.returncode, 0)

    def test_decoder_invalid(self):
        broken_cases = [
            b"z",      
            b"!!!!z",  
            b"abzcd",  
            b"\xff\xff",  
        ]
        for bad_data in broken_cases:
            with self.subTest(bad_data=bad_data):
                result = subprocess.run(
                    ["./ascii85", "-d"],
                    input=bad_data,
                    capture_output=True
                )
                self.assertNotEqual(result.returncode, 0)


if __name__ == '__main__':
    unittest.main()

