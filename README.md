# WordFilter
Filters words given text and sorts them by count. Also cross-references are printed where in the original text the word was given.

# How to use
You can generate the project with [`CMake`](https://cmake.org/download/). Just make sure you have [`Git`](https://git-scm.com/download/) in order to download [`GoogleTest`](https://github.com/google/googletest) for test project support. Otherwise, use CMake just on the `WordFilter/` folder.

Place desired text in a file

# Changelog
### Patch [v1.0](https://github.com/abelzis/WordFilter/releases/tag/v1.0) (2019-05-21)
**Added**
  - Filtering words from file
  - Exporting filtered words by count or by first alphabetical letter
  - Ability to open file or create one with default text
