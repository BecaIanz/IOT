import pyads
# ARRUMAR AQUI
plc = pyads.Connection('10.234.196.113.1.1', pyads.PORT_TC3PLC1, '10.234.196.113')
plc.open()

while True:
        
    i = int(input("Valor: "))
    
    plc.write_by_name("GVL.robotStatus", i)

plc.close()
