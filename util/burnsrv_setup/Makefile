.PHONY: clean run debug

arm_files = bbc1/vidshere.txt config/default \
			config/nginx.conf modrtmp-arm \
			setup2.sh README.md www

setup2.zip : Makefile
	zip -r setup2.zip $(arm_files)

armzip: setup2.zip

