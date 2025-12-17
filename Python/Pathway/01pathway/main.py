import pathway as pw

class Schema(pw.Schema):
    id: int
    value: int

table = pw.io.csv.read(
    "input.csv",
    schema=Schema,
    mode="static"  # since file doesn't change
)

result = table.with_columns(
    doubled = table.value * 2
)

pw.debug.compute_and_print(result)
