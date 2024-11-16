import matplotlib.pyplot as plt

# Function to plot the execution times for both methods
def plot_execution_times(sizes, recursive_times, iterative_times):
    plt.plot(sizes, recursive_times, label='Recursive Insertion', marker='o')
    plt.plot(sizes, iterative_times, label='Iterative Insertion', marker='o')
    
    # Adding title and labels
    plt.title('Execution Time Comparison: Recursive vs Iterative BST Insertion')
    plt.xlabel('Number of Elements')
    plt.ylabel('Execution Time (seconds)')
    
    # Add grid, legend, and show the plot
    plt.grid(True)
    plt.legend()
    plt.show()

# Main function to take input and plot the graph
def main():
    # Pre-defined tree sizes
    sizes = [5, 10, 15]

    # Input the execution times for recursive insertion
    recursive_times = []
    print("Enter the execution times for recursive insertion:")
    for size in sizes:
        time = float(input(f"Recursive Time for size {size}: "))
        recursive_times.append(time)

    # Input the execution times for iterative insertion
    iterative_times = []
    print("\nEnter the execution times for iterative insertion:")
    for size in sizes:
        time = float(input(f"Iterative Time for size {size}: "))
        iterative_times.append(time)

    # Plot the graph
    plot_execution_times(sizes, recursive_times, iterative_times)

# Run the main function
if __name__ == "__main__":
    main()
