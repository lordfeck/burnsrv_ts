# Common functions for Bash CGI
# Author: MJB Authored: 06-12-19
# Include at the top of all CGI scripts.
# Capable of rendering either HTML or JSON.

# WriteParagraph
function wP {
	echo "<p>$1</p>"
}

# WriteHeading format: TEXT HEADER_LEVEL (def. 1)
function wH {
    echo "<h${2:-1}>$1</h${2:-1}>"
}

# Necessary for the CGI wrapper to serve HTML
function writeHeader {
    echo -e 'Content-type: text/html\n'
    echo "<!DOCTYPE html>"
    echo "<head>"
    echo "<title>$1</title>"
    echo '<body style="color:#ffffff; background-color:#000000;">'
}

function writeFooter {
    echo "</body>"
    echo "</html>"
}

function writeList {
    echo -n "<p>";
    for element in "$@"; do
        echo "$element<br>";
    done
    echo -n "</p>";
}

# === BEGIN JSON FUNCTIONS === #

function writeJSONHeader {
    echo -e 'Content-type: application/json\n'
}

#JSON TAG
function jT {
    echo -n "\"$1\":"
}

#JSON FIELD
function jF {
    # JSON expects a comma after each field until the final
    if [ "$2" = "f" ]; then
        echo "\"$1\""
    else
        echo "\"$1\","
    fi
}
