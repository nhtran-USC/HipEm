#! /usr/bin/env ruby

# compare two image files (in our text-based format)
# to see if they are identical (in terms of the width/height
# and the pixel data values)

raise "No!" if ARGV.length != 2

img1_filename = ARGV[0]
img2_filename = ARGV[1]

DEC = /^[0-9]+$/
HEX = /^[0-9a-fA-F]+$/

class Image
  attr_reader :width, :height, :cvals

  def initialize
    @width = nil
    @height = nil
    @cvals = []
  end

  def push_cval(cval)
    @cvals.push(cval)
  end

  def _parse(line)
    tokens = line.split(/\s+/)
    tokens.each do |token|
      if @width.nil?
        @width = self._parse_dec(token)
      elsif @height.nil?
        @height = self._parse_dec(token)
      else
        cval = self._parse_hex(token)
        self.push_cval(cval)
      end
    end
  end

  def _parse_dec(token)
    raise "Invalid width or height" if !DEC.match?(token)
    return token.to_i
  end

  def _parse_hex(token)
    raise "Invalid hex value" if !HEX.match?(token)
    cval = token.to_i(16)
    raise "Invalid color value" if cval > 255
    return cval
  end

  def self.read(inf)
    img = Image.new
    inf.each_line do |line|
      img._parse(line.strip)
    end
    return img
  end
end

img1 = nil
img2 = nil

File.open(img1_filename) { |inf| img1 = Image.read(inf) }
File.open(img2_filename) { |inf| img2 = Image.read(inf) }

if img1.width != img2.width
  puts "Widths differ"
  exit 1
end

if img1.height != img2.height
  puts "Heights differ"
  exit 1
end

if img1.cvals.length != img2.cvals.length
  puts "Number of pixel data values differ"
  exit 1
end

if img1.cvals != img2.cvals
  puts "Pixel data values differ"
  exit 1
end

puts "Image files are identical!"
exit 0
