import pyads

NetId = "10.234.193.182.1.1"
ipDestino = "10.234.193.182"
Port = 851

plc = pyads.Connection(NetId, Port, ipDestino)

plc.open()

tempo = plc.read_by_name("GVL.tempo", pyads.PLCTYPE_INT)

print(f"Antes de mudar:{tempo}")
plc.write_by_name("GVL.tempo", 7 , pyads.PLCTYPE_INT)

tempo = plc.read_by_name("GVL.tempo", pyads.PLCTYPE_INT)
print(f"Depois de mudar:{tempo}")

plc.close()