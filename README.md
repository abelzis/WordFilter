# WordFilter
Filters words given text and sorts them by count. Also cross-references are printed where in the original text the word was given.

# How to use
You can generate the project with [`CMake`](https://cmake.org/download/). Just make sure you have [`Git`](https://git-scm.com/download/) in order to download [`GoogleTest`](https://github.com/google/googletest) for test project support. Otherwise, use CMake just in the `WordFilter/` folder.

Follow the instructions and please insert desired text to filter out words.

# Results
After scanning the text, app creates a cross-reference for all the words mentioned in the text (if count > 1 by default). For example, given text from [Oracle](https://www.oracle.com/sun/), results after running the app:

![Results](https://i.gyazo.com/f33eae0db5812f02aad6eb4bba0b275f.png)

Also, URL scanning is true, if an URL is present in the text. In e.g. [source](https://www.intelligenteconomist.com/url-shortener-services/) outputs:

![URLs](https://i.gyazo.com/0cacec403df0f8019a8f6e3458aa803d.png)

Have fun!

# Changelog
### Patch EXAM [v1.1](https://github.com/abelzis/WordFilter/releases/tag/v1.1) (2019-06-11)
**Changed**
  - Structure of output files.
  
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
