import pathway as pw
class InputSchemae(pw.Schema):
    value: int
input_table = pw.io.csv.read(
    "input"
)