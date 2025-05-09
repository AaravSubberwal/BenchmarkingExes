import os
import subprocess
import time
import platform
import shutil
from pathlib import Path

def clear_screen():
    """Clear the terminal screen based on OS."""
    os.system('cls' if platform.system() == 'Windows' else 'clear')

def print_header():
    """Print the application header."""
    print("=" * 60)
    print("             MULTI-LANGUAGE BENCHMARK TOOL")
    print("=" * 60)
    print("Compare performance of C, C++, and Rust implementations")
    print("-" * 60)

def get_file_name():
    """Get the base filename from user input."""
    while True:
        file_name = input("Enter the base name of your implementation (without extension): ").strip()
        
        # Check if all required files exist
        c_file = Path(f"c/{file_name}.c")
        cpp_file = Path(f"cpp/{file_name}.cpp")
        rust_file = Path(f"rust/src/{file_name}.rs")
        
        if not c_file.exists():
            print(f"Error: {c_file} not found")
        elif not cpp_file.exists():
            print(f"Error: {cpp_file} not found")
        elif not rust_file.exists():
            print(f"Error: {rust_file} not found")
        else:
            return file_name

def compile_c(file_name):
    """Compile C implementation."""
    print(f"Compiling C implementation ({file_name}.c)...")
    
    output_path = f"c/{file_name}"
    if platform.system() == "Windows":
        output_path += ".exe"
    
    try:
        subprocess.run(
            ["gcc", f"c/{file_name}.c", "-O2", "-o", output_path],
            check=True,
            capture_output=True
        )
        return output_path
    except subprocess.CalledProcessError as e:
        print(f"C compilation failed: {e.stderr.decode()}")
        return None

def compile_cpp(file_name):
    """Compile C++ implementation."""
    print(f"Compiling C++ implementation ({file_name}.cpp)...")
    
    output_path = f"cpp/{file_name}"
    if platform.system() == "Windows":
        output_path += ".exe"
    
    try:
        subprocess.run(
            ["g++", f"cpp/{file_name}.cpp", "-O2", "-o", output_path],
            check=True,
            capture_output=True
        )
        return output_path
    except subprocess.CalledProcessError as e:
        print(f"C++ compilation failed: {e.stderr.decode()}")
        return None

def compile_rust(file_name):
    """Compile Rust implementation."""
    print(f"Compiling Rust implementation ({file_name}.rs)...")
    
    try:
        cargo_toml_path = "rust/Cargo.toml"
        with open(cargo_toml_path, 'r') as f:
            cargo_content = f.read()
        
        binary_entry = f'name = "{file_name}"'
        
        if binary_entry not in cargo_content:
            with open(cargo_toml_path, 'a') as f:
                f.write(f'\n[[bin]]\nname = "{file_name}"\npath = "src/{file_name}.rs"\n')
        
        os.chdir("rust")
        subprocess.run(
            ["cargo", "build", "--release", "--bin", file_name],
            check=True,
            capture_output=True
        )
        os.chdir("..")
        
        if platform.system() == "Windows":
            output_path = f"rust/target/release/{file_name}.exe"
        else:
            output_path = f"rust/target/release/{file_name}"
        
        return output_path
    
    except subprocess.CalledProcessError as e:
        print(f"Rust compilation failed: {e.stderr.decode()}")
        return None
    except Exception as e:
        print(f"Rust setup failed: {str(e)}")
        return None

def benchmark(executable_path, runs=20):
    """Run the executable multiple times and measure performance."""
    if not executable_path or not Path(executable_path).exists():
        return None
    
    print(f"Running {Path(executable_path).name}...")
    
    execution_times = []
    for i in range(runs):
        start_time = time.time()
        
        try:
            result = subprocess.run(
                [executable_path], 
                check=True,
                capture_output=True
            )
            
            end_time = time.time()
            execution_time = (end_time - start_time) * 1000  # Convert to milliseconds
            execution_times.append(execution_time)
            
            if i == 0:  # Show output only for the first run
                print(f"Output: {result.stdout.decode().strip()}")
        
        except subprocess.CalledProcessError as e:
            print(f"Execution failed: {e.stderr.decode()}")
            return None
    
    if runs >= 3:
        execution_times.remove(max(execution_times))
        execution_times.remove(min(execution_times))
    
    try:
        os.remove(executable_path)
    except Exception as e:
        print(f"Warning: Failed to delete {executable_path}: {e}")

    return sum(execution_times) / len(execution_times)

def display_results(results):
    """Display benchmark results in a nice table."""
    print("\n" + "=" * 60)
    print("                BENCHMARK RESULTS")
    print("=" * 60)
    
    valid_results = {lang: time for lang, time in results.items() if time is not None}
    if valid_results:
        fastest_lang = min(valid_results, key=valid_results.get)
    else:
        fastest_lang = None
    
    print(f"{'Language':<15} | {'Time (ms)':<15} | {'Relative':<15}")
    print("-" * 50)
    
    for lang, time in results.items():
        if time is not None:
            if fastest_lang and valid_results[fastest_lang] > 0:
                relative = time / valid_results[fastest_lang]
                relative_str = f"{relative:.2f}x"
                if lang == fastest_lang:
                    relative_str = "1.00x (fastest)"
            else:
                relative_str = "N/A"
                
            print(f"{lang:<15} | {time:.4f} ms{' ' * (15 - len(f'{time:.4f} ms'))} | {relative_str}")
        else:
            print(f"{lang:<15} | Failed{' ' * 9} | N/A")
    
    print("=" * 60)

def main():
    clear_screen()
    print_header()
    while(1):
        """Main function to run the benchmark."""
        
        file_name = get_file_name()
        
        c_executable = compile_c(file_name)
        cpp_executable = compile_cpp(file_name)
        rust_executable = compile_rust(file_name)
        
        print("\nRunning benchmarks...")
        results = {
            "C": benchmark(c_executable),
            "C++": benchmark(cpp_executable),
            "Rust": benchmark(rust_executable)
        }
        
        # Display results
        display_results(results)
        
        print("\nBenchmark complete!")

if __name__ == "__main__":
    main()