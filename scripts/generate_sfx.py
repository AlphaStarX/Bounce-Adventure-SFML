"""
Generate simple retro-style sound effects as WAV files for Bounce Adventure.
Produces: jump, coin, hazard, checkpoint, and goal complete sounds.
"""
import struct
import math
import wave
import os

SAMPLE_RATE = 44100
BITS_PER_SAMPLE = 16
MAX_AMP = 32767
OUT_DIR = os.path.join(os.path.dirname(os.path.dirname(__file__)), "assets", "sounds")


def write_wav(path: str, samples: list[float]) -> None:
    """Write a list of float samples (-1.0..1.0) to a 16-bit mono WAV file."""
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with wave.open(path, "w") as wf:
        wf.setnchannels(1)
        wf.setsampwidth(BITS_PER_SAMPLE // 8)
        wf.setframerate(SAMPLE_RATE)
        for s in samples:
            clamped = max(-1.0, min(1.0, s))
            wf.writeframesraw(struct.pack("<h", int(clamped * MAX_AMP)))


def adsr_envelope(duration: float, attack: float, decay: float, sustain: float, release: float) -> list[float]:
    """Generate an ADSR envelope for the given total duration."""
    total_samples = int(duration * SAMPLE_RATE)
    attack_samples = int(attack * SAMPLE_RATE)
    decay_samples = int(decay * SAMPLE_RATE)
    release_samples = int(release * SAMPLE_RATE)
    sustain_samples = max(0, total_samples - attack_samples - decay_samples - release_samples)

    envelope = []
    # Attack
    for i in range(attack_samples):
        envelope.append(i / max(1, attack_samples))
    # Decay
    for i in range(decay_samples):
        t = i / max(1, decay_samples)
        envelope.append(1.0 - (1.0 - sustain) * t)
    # Sustain
    for _ in range(sustain_samples):
        envelope.append(sustain)
    # Release
    for i in range(release_samples):
        t = i / max(1, release_samples)
        envelope.append(sustain * (1.0 - t))
    return envelope


def jump_sound() -> list[float]:
    """Rising pitch blip — energetic jump SFX (~0.15s)."""
    duration = 0.15
    env = adsr_envelope(duration, attack=0.005, decay=0.05, sustain=0.3, release=0.095)
    samples = []
    for i, e in enumerate(env):
        t = i / SAMPLE_RATE
        freq = 300 + 900 * (t / duration)  # Rising sweep 300→1200 Hz
        s = math.sin(2.0 * math.pi * freq * t) * e * 0.7
        samples.append(s)
    return samples


def coin_sound() -> list[float]:
    """Two-tone ding — coin pickup (~0.2s)."""
    duration = 0.2
    env = adsr_envelope(duration, attack=0.003, decay=0.08, sustain=0.2, release=0.117)
    samples = []
    for i, e in enumerate(env):
        t = i / SAMPLE_RATE
        # Two harmonics for a bright "coin" sound
        s = (math.sin(2.0 * math.pi * 1318 * t) * 0.5 +
             math.sin(2.0 * math.pi * 1760 * t) * 0.5) * e * 0.6
        samples.append(s)
    return samples


def hazard_sound() -> list[float]:
    """Harsh noise burst — damage taken (~0.25s)."""
    duration = 0.25
    env = adsr_envelope(duration, attack=0.002, decay=0.06, sustain=0.15, release=0.188)
    samples = []
    for i, e in enumerate(env):
        t = i / SAMPLE_RATE
        # Low growl + high buzz
        s = (math.sin(2.0 * math.pi * 150 * t) * 0.4 +
             math.sin(2.0 * math.pi * 1100 * t) * 0.4) * e * 0.7
        samples.append(s)
    return samples


def checkpoint_sound() -> list[float]:
    """Ascending arpeggio — checkpoint activated (~0.3s)."""
    duration = 0.3
    env = adsr_envelope(duration, attack=0.01, decay=0.1, sustain=0.3, release=0.19)
    notes = [523, 659, 784]  # C5, E5, G5
    note_duration = duration / len(notes)
    samples = []
    for i, e in enumerate(env):
        t = i / SAMPLE_RATE
        note_idx = min(int(t / note_duration), len(notes) - 1)
        freq = notes[note_idx]
        s = math.sin(2.0 * math.pi * freq * t) * e * 0.6
        samples.append(s)
    return samples


def goal_sound() -> list[float]:
    """Triumphant fanfare — level complete (~0.5s)."""
    duration = 0.5
    env = adsr_envelope(duration, attack=0.02, decay=0.1, sustain=0.5, release=0.38)
    # C-E-G-C major chord arpeggio
    notes = [523, 659, 784, 1047]
    note_duration = duration / len(notes)
    samples = []
    for i, e in enumerate(env):
        t = i / SAMPLE_RATE
        note_idx = min(int(t / note_duration), len(notes) - 1)
        freq = notes[note_idx]
        s = (math.sin(2.0 * math.pi * freq * t) * 0.5 +
             math.sin(2.0 * math.pi * freq * 2 * t) * 0.2) * e * 0.6
        samples.append(s)
    return samples


def main() -> None:
    sounds = {
        "jump.wav": jump_sound(),
        "coin.wav": coin_sound(),
        "hazard.wav": hazard_sound(),
        "checkpoint.wav": checkpoint_sound(),
        "goal.wav": goal_sound(),
    }
    for name, samples in sounds.items():
        path = os.path.join(OUT_DIR, name)
        write_wav(path, samples)
        print(f"Generated: {path}")


if __name__ == "__main__":
    main()
