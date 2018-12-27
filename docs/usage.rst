Usage
=====

In this section we describe how to use the Arduino Serial fixture and how to
use a number of additional convenience functions. We assume that the library is
installed in the directory where the unit tests reside.


Compilation
-----------

First compile the fixture.

::

    g++ -c arduino-serial-fixture/src/Arduino.cc

For all tests that require the serial interface, i.e., tests that require
``Arduino.h``, make sure that the path to the fixture is set.

::

    g++ -I arduino-serial-fixture/src -c test_something.cc

Finally, compile the test main code and link.

::

    g++ -o run_tests test_lib.cc test_something.o Arduino.o


Library
-------

The fixture includes most commonly used functions for serial communication.
Additionally, some convenience functions are included to make testing easier.
These functions can be accessed by including the header.

.. code:: cpp

    #include <Arduino.h>

Easy reading and writing
^^^^^^^^^^^^^^^^^^^^^^^^

The functions ``autoRead()`` and ``autoWrite()`` can be used to read or write
to the serial device. These functions take care of type encoding automatically.
If, for example, we want to read an integer and a float, we use ``autoRead()``
as follows.

.. code:: cpp

    int i = Serial.autoRead<int>();
    float f = Serial.autoRead<float>();

Conversely, easy writing of an integer and a float can be done with
``autoWrite()`` as follows.

.. code:: cpp

    autoWrite(1234);
    autoWrite(3.14F);

Inspecting and preparing data
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The functions ``inspect()`` and ``prepare()`` can be used to inspect the output
buffer and to prepare the input buffer. The ``inspect()`` function works like
the ``autoRead()`` function, except that it operates on the output buffer and
does not change any of the internal buffer offsets. If for example, the output
buffer contains the string ``xyz``, we can use ``inspect()`` as follows.

.. code:: cpp

    String s = Serial.inspect<String>(); // Yields "xyz".
    char c = Serial.inspect<char>(); // Yields 'x'.

The function ``prepare()`` is used to prepare the input buffer. It accepts an
arbitrary amount of variables that are of either basic types (e.g., int, char,
float, etc.) or of type String. If for example, we want to put a char, a string
and an integer in the input buffer, we can use ``prepare()`` as follows.

.. code:: cpp

    Serial.prepare('c', "xyz", 10);
