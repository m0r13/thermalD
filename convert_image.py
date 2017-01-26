#!/usr/bin/env python3

from PIL import Image
import sys

if __name__ == "__main__":
    img = Image.open(sys.argv[1])
    if img.size[0] > img.size[1]:
        img = img.transpose(Image.ROTATE_90)
    target_width = 384
    factor = float(target_width) / img.size[0]
    img = img.resize((target_width, int(factor * img.size[1])))
    img = img.convert("1")
    img.save("out.png")

    #byte_width = int((img.size[0] + 7.0) / 8)
    #byte_height = img.size[1]
    #print(byte_width, byte_height)

    print("#ifndef image_h")
    print("#define image_h")
    print("#define image_width %d" % img.size[0])
    print("#define image_height %d" % img.size[1])
    print("static const uint8_t image_data[] = {")
    px = img.load()
    for row in range(img.size[1]):
        cur_byte = 0
        for column in range(img.size[0]):
            byte_pos = column % 8
            if byte_pos == 0:
                cur_byte = 0
            c = px[column, row]
            assert c == 0 or c == 255
            if c == 0:
                cur_byte = cur_byte | (1 << (7 - byte_pos))

            if byte_pos == 7:
                print(hex(cur_byte), end=", ")
        print()
    print("};")
    print("#endif")
