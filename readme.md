# Embedded TDD Lecture Demo

This is a demo project used in a lecture about Embedded TDD using PlatformIO, Unity, fff and FakeIt.

## Red-Green
I'm using dose to demo TDD usage with PIO:
```bash
pip install dose
```

You may run all the test:
```bash
dose "pio test -v 2>&1"
```

or a specific submodule:
```bash
dose "pio test -v -f test_fakeit 2>&1"
```