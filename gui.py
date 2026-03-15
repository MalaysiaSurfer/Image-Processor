import customtkinter as ctk
from tkinter import filedialog
from PIL import Image, ImageTk
import subprocess
import os
import tempfile

applied_once = False

ctk.set_appearance_mode("dark")
ctk.set_default_color_theme("dark-blue")

root = ctk.CTk()
root.title("Image Processor")
root.geometry("900x600")

input_path = None
tmp_output = tempfile.mktemp(suffix=".bmp")
tmp_input = tempfile.mktemp(suffix=".bmp")

left_panel = ctk.CTkFrame(root, width=250, fg_color="#8D003B", corner_radius=0)
left_panel.pack(side="left", fill="y")
left_panel.pack_propagate(False)

right_panel = ctk.CTkFrame(root, fg_color="#1e1e1e", corner_radius=0)
right_panel.pack(side="right", fill="both", expand=True)

preview_label = ctk.CTkLabel(right_panel, text="")
preview_label.pack(expand=True)

def open_file():
    global input_path
    path = filedialog.askopenfilename(filetypes=[("Images", "*.jpg *.jpeg *.png *.bmp")])
    if path:
        input_path = path
        show_preview(path)

def show_preview(path):
    img = Image.open(path)
    img.thumbnail((600, 500))
    ctk_image = ctk.CTkImage(light_image=img, dark_image=img, size=img.size)
    preview_label.configure(image=ctk_image)
    preview_label.image = ctk_image

def save_file():
    if not input_path:
        return
    base = os.path.splitext(os.path.basename(input_path))[0]
    save_path = filedialog.asksaveasfilename(
        initialfile=base + "_new",
        defaultextension=".png",
        filetypes=[("PNG", "*.png"), ("JPEG", "*.jpg"), ("BMP", "*.bmp")]
    )
    if save_path:
        Image.open(tmp_output).save(save_path)

def apply_filters():
    global applied_once
    if not input_path:
        return
    
    if applied_once:
        Image.open(tmp_output).save(tmp_input)
    else:
        Image.open(input_path).save(tmp_input)
        applied_once = True

    processor = os.path.join(os.path.dirname(__file__), "image_processor")
    args = [processor, tmp_input, tmp_output]
    if gs_var.get():    args += ["-gs"]
    if neg_var.get():   args += ["-neg"]
    if sharp_var.get(): args += ["-sharp"]
    if edge_var.get():  args += ["-edge", edge_threshold.get()]
    if blur_var.get():  args += ["-blur", blur_sigma.get()]
    if twirl_var.get(): args += ["-twirl", twirl_radius.get(), twirl_angle.get()]
    subprocess.run(args)
    show_preview(tmp_output)

def reset():
    global applied_once
    applied_once = False
    if input_path:
        show_preview(input_path)

def make_button(parent, text, command):
    btn = ctk.CTkButton(parent, text=text, fg_color="#63DC90", hover=False,
                        command=None,
                        text_color="#00782D", font=("system", 18, "bold"))
    
    if command != apply_filters:
        btn.configure(command=command)
    
    btn.after(100, lambda: btn.configure(text_color="#00782D", fg_color="#63DC90"))
    
    def on_enter(e): btn.configure(text_color="#63DC90", fg_color="#00782D")
    def on_leave(e): btn.configure(text_color="#00782D", fg_color="#63DC90")
    def on_click(e):
        btn.configure(text_color="#00782D", fg_color="#63DC90")
        if command == apply_filters: 
            btn.after(140, lambda: btn.configure(text_color="#63DC90", fg_color="#00782D"))
            btn.after(1, command)


    btn.bind("<Enter>", on_enter)
    btn.bind("<Leave>", on_leave)
    btn.bind("<Button-1>", on_click)

    return btn

open_btn = make_button(left_panel, "Open file", open_file).pack(pady=10, padx=10, fill="x")

save_btn = make_button(left_panel, "Save", save_file).pack(pady=5, padx=10, fill="x", side="bottom")

reset_button = make_button(left_panel, "Reset", reset).pack(pady=10, padx=10, fill="x", side="bottom")

apply_btn = make_button(left_panel, "Apply", apply_filters).pack(pady=5, padx=10, fill="x", side="bottom")

ctk.CTkLabel(left_panel, text="Filters", text_color="#E2FA00", font=("system", 21, "bold")).pack(pady=(15,5))

gs_var = ctk.BooleanVar()
neg_var = ctk.BooleanVar()
sharp_var = ctk.BooleanVar()

ctk.CTkCheckBox(left_panel, text="Grayscale", variable=gs_var, fg_color="#6B0029", hover_color="#550020", font=("system", 15, "bold")).pack(anchor="w", padx=15, pady=(15,0))
ctk.CTkCheckBox(left_panel, text="Negative", variable=neg_var, fg_color="#6B0029", hover_color="#550020", font=("system", 15, "bold")).pack(anchor="w", padx=15, pady=(12,0))
ctk.CTkCheckBox(left_panel, text="Sharpening", variable=sharp_var, fg_color="#6B0029", hover_color="#550020", font=("system", 15, "bold")).pack(anchor="w", padx=15, pady=(12,0))

edge_var = ctk.BooleanVar()
ctk.CTkCheckBox(left_panel, text="Edge Detection", variable=edge_var, fg_color="#6B0029", hover_color="#550020", font=("system", 15, "bold")).pack(anchor="w", padx=15, pady=(27,0))
edge_row = ctk.CTkFrame(left_panel, fg_color="#8D003B")
edge_row.pack(anchor="w", padx=15)
edge_threshold = ctk.CTkEntry(edge_row, width=60, border_color="#00782D")
edge_threshold.insert(0, "0.2")
edge_threshold.pack(side="left", pady=(3, 0))
ctk.CTkLabel(edge_row, text="Threshold", font=("system", 12, "bold")).pack(side="left", padx=5)

blur_var = ctk.BooleanVar()
ctk.CTkCheckBox(left_panel, text="Blur", variable=blur_var, fg_color="#6B0029", hover_color="#550020", font=("system", 15, "bold")).pack(anchor="w", padx=15, pady=(12,0))
blur_row = ctk.CTkFrame(left_panel, fg_color="#8D003B")
blur_row.pack(anchor="w", padx=15)
blur_sigma = ctk.CTkEntry(blur_row, width=60, border_color="#00782D")
blur_sigma.insert(0, "1.0")
blur_sigma.pack(side="left", pady=(3, 0))
ctk.CTkLabel(blur_row, text="Sigma", font=("system", 12, "bold")).pack(side="left", padx=5)

twirl_var = ctk.BooleanVar()
ctk.CTkCheckBox(left_panel, text="Twirl", variable=twirl_var, fg_color="#6B0029", hover_color="#550020", font=("system", 15, "bold")).pack(anchor="w", padx=15, pady=(15,0))

twirl_radius_row = ctk.CTkFrame(left_panel, fg_color="#8D003B")
twirl_radius_row.pack(anchor="w", padx=15)
twirl_radius = ctk.CTkEntry(twirl_radius_row, width=60, border_color="#00782D")
twirl_radius.insert(0, "300")
twirl_radius.pack(side="left", pady=(3, 0))
ctk.CTkLabel(twirl_radius_row, text="Radius", font=("system", 12, "bold")).pack(side="left", padx=5)

twirl_angle_row = ctk.CTkFrame(left_panel, fg_color="#8D003B")
twirl_angle_row.pack(anchor="w", padx=15)
twirl_angle = ctk.CTkEntry(twirl_angle_row, width=60, border_color="#00782D")
twirl_angle.insert(0, "5")
twirl_angle.pack(side="left", pady=(3, 0))
ctk.CTkLabel(twirl_angle_row, text="Angle", font=("system", 12, "bold")).pack(side="left", padx=5)

root.mainloop()