.PHONY: clean 

arm_files = bbc1/vidshere.txt config/default \
			config/nginx.conf modrtmp-arm \
			setup.sh setup.config README.md www

setup.zip : Makefile
	zip -r setup.zip $(arm_files)

armzip: setup.zip

clean:
	rm -f setup.zip
