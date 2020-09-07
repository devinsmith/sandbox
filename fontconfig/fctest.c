#include <fontconfig/fontconfig.h>
#include <fontconfig/fcfreetype.h>

#include <stdio.h>

static void dump_font_info(FcPattern *pattern)
{
  FcChar8 *path, *psName, *family, *style;
  int weight, width, slant, spacing;

  FcPatternGetString(pattern, FC_FILE, 0, &path);
  FcPatternGetString(pattern, FC_POSTSCRIPT_NAME, 0, &psName);
  FcPatternGetString(pattern, FC_FAMILY, 0, &family);
  FcPatternGetString(pattern, FC_STYLE, 0, &style);

  FcPatternGetInteger(pattern, FC_WEIGHT, 0, &weight);
  FcPatternGetInteger(pattern, FC_WIDTH, 0, &width);
  FcPatternGetInteger(pattern, FC_SLANT, 0, &slant);
  FcPatternGetInteger(pattern, FC_SPACING, 0, &spacing);

  printf("File: %s\n", path);
  printf("PS Name: %s\n", psName);
  printf("Family: %s\n", family);
  printf("Style: %s\n", style);
}

int main(int argc, char *argv[])
{
  FcInit();
  FcConfigAppFontAddFile(FcConfigGetCurrent(),
    (const FcChar8 *)"./TwemojiMozilla.ttf");

  FcPattern *pattern = FcPatternCreate();
  FcPatternAddString(pattern, FC_FAMILY, (FcChar8 *)"Twemoji Mozilla");

  FcResult result;
  FcPattern *font = FcFontMatch(NULL, pattern, &result);

  if (result == FcResultMatch) {
    dump_font_info(font);
  } else {
    printf("No such font found\n");
  }

  return 0;
}
