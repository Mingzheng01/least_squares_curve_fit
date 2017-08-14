
# Creates a folder with a specified name if it does not exist already
create_folder() {

  # if the bin folder does not exist
  if [ ! -d $1 ]; then
    echo "Creating $1 directory"
    mkdir $1
    echo "$1 directory successfull created"

  else
    echo "$1 directory already exists"
  fi
}

#-------------------------------------------------------------------------------

# Prompt to install a given package via brew
prompt_brew_install() {

  while true; do
    read -p "$1 is  not installed, would you like to install it? (yes or no) " yn
    case $yn in
        [Yy]* ) brew_install $1; break;;
        [Nn]* ) exit;;
        * ) echo "Please answer yes or no.";;
    esac
  done
}

#-------------------------------------------------------------------------------

# Verifies is a given package is installed
verify_installed() {
  echo "Checking that $1 is installed..."

  OUTPUT=$(which $1)

  if [ "$OUTPUT" = "" ]; then
    prompt_brew_install $1

  else
    echo "$1 is installed"
  fi
}

#-------------------------------------------------------------------------------

# Install homebrew
install_brew() {
  BREW="brew"

  echo "Checking that $BREW installed"

  OUTPUT=$(which $BREW)

  if [ "$OUTPUT" = "" ]; then
    echo "$BREW is not installed..."
    echo "Installing $BREW..."
    /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
  else
    echo "$BREW is already installed..."
  fi
}

#-------------------------------------------------------------------------------

# Install a specified package
brew_install() {
  brew install $1
  brew link --overwrite $1
}

#-------------------------------------------------------------------------------

# Installs python packages
install_python_dependencies() {
  declare -a dependencies=('matplotlib' 'tkinter');

  for i in "${dependencies[@]}"; do
    pip3 install $i
  done
}

#-------------------------------------------------------------------------------

# Installs system dependencies
install_system_depencies() {
  declare -a dependencies=('python3' 'cmake');

  for i in "${dependencies[@]}"; do
    verify_installed $i
  done
}

#-------------------------------------------------------------------------------

# Build the C++ code
build_cpp() {
  create_folder bin
  cmake .
  make
}

#-------------------------------------------------------------------------------

# Launch Python app
launch_app() {
  cd src/py
  python3 main.py
}

#-------------------------------------------------------------------------------

# Make sure that brew is installed
install_brew

# Install system dependencies such as python3 and cmake
install_system_depencies

# Install python3 packages
install_python_dependencies

# Build the C++ app
build_cpp

# Launch the app
launch_app
