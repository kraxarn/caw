#!/bin/bash

magick \
	-background transparent \
	"../../MaterialDesign-SVG/svg/$1.svg" \
	-fill "#fbf5ef" -colorize 100 \
	"icons/$1.qoi"
