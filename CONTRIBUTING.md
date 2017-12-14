Contributions to the library are gladly accepted.

The main development happens in https://github.com/p12tic/libsimdpp repository.

If you don't have time to submit a bug fix, please open an issue report on
GitHub so at least the problem is known. The same applies to improvements -
don't hesitate to open feature request so that the design of new APIs could
take your use case into account.

Documentation
-------------

The documentation is written on a MediaWiki instance which is currently private.
If you find a problem in the documentation, please open an issue with a link to
the page in question.

Code changes
------------

Please test your code changes by running the following:

```
mkdir build
cd build
cmake ..

# on Linux / macOS
make check -j8

# on Windows
cmake --build . --target check
```

Please use the `dev` branch as a target for pull requests. The reason for this
is that the public continuous integration services used by the library cover
only SSE2-AVX2 instruction sets. The rest are periodically tested on a private
test farm. Due to the number of tested compilers and library configurations
this testing is usually done only on each merge from the `dev` branch to
the `master` branch.

Code style
----------

C-style pointer casts are discouraged, use reinterpret_cast for that. For
non-pointer types C-style casts are preferred over static_cast or constructor.
