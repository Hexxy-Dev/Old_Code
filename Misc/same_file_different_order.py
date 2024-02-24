def read_and_sort_lines(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
        lines = [line.strip() for line in lines]
        return sorted(lines)

def compare_files(file1, file2):
    sorted_lines1 = read_and_sort_lines(file1)
    sorted_lines2 = read_and_sort_lines(file2)

    #print(sorted_lines1,'\n','\n','\n',sorted_lines2)

    if sorted_lines1 == sorted_lines2:
        return True
    else:
        return False

if __name__ == "__main__":
    file1_path = 'hmm1'
    file2_path = 'hmm2'

    if compare_files(file1_path, file2_path):
        print("The contents of the files are identical after rearranging.")
    else:
        print("The contents of the files are not identical after rearranging.")
