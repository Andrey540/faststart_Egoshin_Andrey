import subprocess
import os
import os.path
import sys

LIBRARIES = ['github.com/gin-gonic/gin']

def is_windows():
    return sys.platform.startswith('win32')

def get_project_path():
    proj_dir = os.path.join(os.path.dirname(os.path.realpath(__file__)), '..')
    return os.path.realpath(proj_dir)

def get_log_path(name):
    return os.path.join(get_project_path(), "scripts", "logs", name)

class MyProcess(subprocess.Popen):
    def __enter__(self):
        return self

    def __exit__(self, type, value, traceback):
        if self.stdout:
            self.stdout.close()
        if self.stderr:
            self.stderr.close()
        if self.stdin:
            self.stdin.close()
        # Wait for the process to terminate, to avoid zombies.
        self.wait()

def get_all_libraries():
    exe_name = 'server.exe' if sys.platform.startswith('win32') else 'server'
    output_dir = os.path.join('..', '..', 'bin', exe_name)
    for library in LIBRARIES:
        args = ["go", "get", library]
        env = os.environ.copy()
        env["GOPATH"] = get_project_path()
        work_dir = os.path.join(get_project_path())
        with open(get_log_path("go-get-stdout.txt"), 'w') as stdout:
            with open(get_log_path("go-get-stderr.txt"), 'w') as stderr:
                # wait for finished
                with MyProcess(args, cwd=work_dir, env=env, stdout=stdout, stderr=stderr) as proc:
                    proc.communicate()
                    if proc.returncode != 0:
                        print "Go Get failed with return code ", proc.returncode, ", see logs"
                        break

def main():
    get_all_libraries()

if __name__ == '__main__':
    main()
