import os
import xml.etree.ElementTree as ET
import csv

def convert_animdata_xml_to_csv(xml_path, csv_path):
    tree = ET.parse(xml_path)
    root = tree.getroot()
    anims = root.find('Anims')

    with open(csv_path, 'w', newline='', encoding='utf-8') as csvfile:
        fieldnames = ['Name', 'FrameWidth', 'FrameHeight', 'FrameCount']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader()

        for anim in anims.findall('Anim'):
            name = anim.findtext('Name')
            width = anim.findtext('FrameWidth')
            height = anim.findtext('FrameHeight')
            durations = anim.find('Durations')
            if durations is not None:
                frame_count = len(durations.findall('Duration'))
            else:
                frame_count = 0

            if name and width and height:
                writer.writerow({
                    'Name': name,
                    'FrameWidth': width,
                    'FrameHeight': height,
                    'FrameCount': frame_count
                })

def batch_convert_xml_to_csv(root_dir):
    for foldername, subfolders, filenames in os.walk(root_dir):
        for filename in filenames:
            if filename == "AnimData.xml":
                xml_path = os.path.join(foldername, filename)
                csv_path = os.path.join(foldername, "AnimData.csv")
                convert_animdata_xml_to_csv(xml_path, csv_path)
                print(f"Converted: {csv_path}")

batch_convert_xml_to_csv(r'C:\Users\wollo\Desktop\Pokemon_Mystery_Dungeon\Pokemon_Mystery_Dungeon\Pokemon_Mystery_Dungeon\Image\PokemonAnim')