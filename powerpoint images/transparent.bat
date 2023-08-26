cd %CD%
mkdir batch
magick mogrify -format png *.JPG
FOR %%G IN (*.png) DO magick "%%G" -fuzz 50%% -transparent #000000 "batch\%%G"
PAUSE
