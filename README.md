# WordFilter
Filters words given text and sorts them by count. Also cross-references are printed where in the original text the word was given.

# How to use
You can generate the project with [`CMake`](https://cmake.org/download/). Just make sure you have [`Git`](https://git-scm.com/download/) in order to download [`GoogleTest`](https://github.com/google/googletest) for test project support. Otherwise, use CMake just in the `WordFilter/` folder.

Follow the instructions and please insert desired text to filter out words.

# Changelog
### Patch [v1.0.1](https://github.com/abelzis/WordFilter/releases/tag/v1.0.1) (2019-05-31)
**Added**
  - Filtering of URLs
  
**Fixed**
  - Fixed errors with incorrect locations of words
  - Fixed newline bugs

### Patch [v1.0](https://github.com/abelzis/WordFilter/releases/tag/v1.0) (2019-05-22)
**Added**
  - Filtering words from file
  - Exporting filtered words by count or by first alphabetical letter
  - Ability to open file or create one with default text
