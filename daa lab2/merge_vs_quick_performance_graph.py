import matplotlib.pyplot as plt

# Function to plot the execution times for both sorting methods
def plot_execution_times(sizes, merge_times, quick_times):
    plt.plot(sizes, merge_times, label='Merge Sort', marker='o')
    plt.plot(sizes, quick_times, label='Quick Sort', marker='o')
    
    # Adding title and labels
    plt.title('Execution Time Comparison: Merge Sort vs Quick Sort')
    plt.xlabel('Number of Elements')
    plt.ylabel('Execution Time (seconds)')
    
    # Add grid, legend, and show the plot
    plt.grid(True)
    plt.legend()
    plt.show()

# Main function to take input and plot the graph
def main():
    # Pre-defined tree sizes
    sizes = [5, 10, 15, 20]

    # Input the execution times for Merge Sort
    merge_times = []
    print("Enter the execution times for Merge Sort:")
    for size in sizes:
        time = float(input(f"Merge Sort Time for size {size}: "))
        merge_times.append(time)

    # Input the execution times for Quick Sort
    quick_times = []
    print("\nEnter the execution times for Quick Sort:")
    for size in sizes:
        time = float(input(f"Quick Sort Time for size {size}: "))
        quick_times.append(time)

    # Plot the graph
    plot_execution_times(sizes, merge_times, quick_times)

# Run the main function
if __name__ == "__main__":
    main()
